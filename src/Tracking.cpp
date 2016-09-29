
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
#include <jni.h>

#include "org_cripac_isee_vpe_util_Tracking.h"
#include "read_conf.h"
#include "tracking_intf.h"

using namespace std;

JNIEXPORT jbyteArray
JNICALL Java_org_cripac_isee_vpe_util_Tracking_readConfFile
    (JNIEnv *env, jobject obj, jstring buffer) {

  char *rtn = NULL;
  jclass clsstring = env->FindClass("java/lang/String");
  jstring strencode = env->NewStringUTF("GB2312");
  jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
  jbyteArray
  barr = (jbyteArray)
  env->CallObjectMethod(buffer, mid, strencode);
  jsize alen = env->GetArrayLength(barr);
  jbyte *ba = env->GetByteArrayElements(barr, JNI_FALSE);
  if (alen > 0) {
    rtn = (char *) malloc(alen + 1);
    memcpy(rtn, ba, alen);
    rtn[alen] = 0;
  }
  env->ReleaseByteArrayElements(barr, ba, 0);
  std::string conf_path(rtn);
  free(rtn);

  char *conf_buffer = NULL;
  size_t buffer_len = readConfFile(conf_path, conf_buffer);
  conf_buffer = new char[buffer_len];
  buffer_len = readConfFile(conf_path, conf_buffer);
  jbyteArray get_confbytes = (env)->NewByteArray(buffer_len);
  env->SetByteArrayRegion(get_confbytes, 0, buffer_len,
                          (const jbyte *) conf_buffer);
  delete[] conf_buffer;
  return get_confbytes;

  //TODO If the param: "strencode" should be destroyed?
}

JNIEXPORT jlong
JNICALL Java_org_cripac_isee_vpe_util_Tracking_initialize
    (JNIEnv *env, jobject obj, jint w, jint h, jint chns_num, jbyteArray buffer, jint conf_len) {

  jsize buffer_len = (env)->GetArrayLength(buffer);
  jbyte *conf_buffer = new jbyte[buffer_len];
  env->GetByteArrayRegion(buffer, 0, buffer_len, conf_buffer);
  //ObjTracking* tracker = new ObjTracking;
  ObjTracking *tracker;
  int res = tracker->init(w, h, chns_num, (const char *) conf_buffer, conf_len);
  //int res = tracker.init(w, h, chns_num, (const char*)conf_buffer, conf_len);
  if (conf_buffer) {
    delete[] conf_buffer;
    conf_buffer = NULL;
  }
  if (!res) {
    fprintf(stderr, "Error: The tracker initialization FAILED!\n");
    return -1;
  }
  return (jlong)(tracker);
}

JNIEXPORT jint
JNICALL Java_org_cripac_isee_vpe_util_Tracking_dotrack
    (JNIEnv *env, jobject obj, jbyteArray buffer, jlong pointer) {
  // ObjTracking *tracker = (ObjTracking *) pointer;
  ObjTracking *tracker = (ObjTracking *) pointer;
  jsize buffer_len = (env)->GetArrayLength(buffer);
  jbyte *frame = new jbyte[buffer_len];
  env->GetByteArrayRegion(buffer, 0, buffer_len, frame);
  int res = tracker->doTrack((const unsigned char *) (frame));
  if (!res) {
    return -1;
  }
  return 1;
}

JNIEXPORT jobjectArray
JNICALL Java_org_cripac_isee_vpe_util_Tracking_getTargets
    (JNIEnv *env, jobject obj, jlong pointer) {
  ObjTracking *tracker = (ObjTracking *) pointer;
  int tracks_num = 0;
  Trajectory *tracks = NULL;
  tracks = tracker->getTrajs(tracks_num);
  printf("trajs_num = %d\n", tracks_num);
  jclass class_Track = env->FindClass("org/cripac/isee/vpe/util/Track");
  if (class_Track == NULL) {
    fprintf(stderr, "Error:Can't find Class:org/cripac/isee/vpe/util/Track");
    return NULL;
  }
  jclass class_Track_BoundingBox = env->FindClass("org/cripac/isee/vpe/util/Track$BoundingBox");
  if (class_Track_BoundingBox == NULL) {
    fprintf(stderr, "Error:Can't find Class:org/cripac/isee/vpe/util/Track$BoundingBox");
    return NULL;
  }

  jmethodID Track_constructor = env->GetMethodID(class_Track, "<init>", "()V");
  jfieldID locationSequence_id =
      env->GetFieldID(class_Track, "locationSequence", "[Lorg/cripac/isee/vpe/util/Track$BoundingBox;");

  jmethodID Track_BoundingBox_constructor = env->GetMethodID(class_Track_BoundingBox, "<init>", "()V");
  jfieldID BB_x_id = env->GetFieldID(class_Track_BoundingBox, "x", "I");
  jfieldID BB_y_id = env->GetFieldID(class_Track_BoundingBox, "y", "I");
  jfieldID BB_width_id = env->GetFieldID(class_Track_BoundingBox, "width", "I");
  jfieldID BB_height_id = env->GetFieldID(class_Track_BoundingBox, "height", "I");
  jfieldID BB_patchData_id = env->GetFieldID(class_Track_BoundingBox, "patchData", "[B");

  jobjectArray Return_TracksList = env->NewObjectArray((jsize) tracks_num, class_Track, 0);
  for (int i = 0; i < tracks_num; ++i) {
    //printf("Start\n");
    jobject Temp_Tracks = env->NewObject(class_Track, Track_constructor);
    jobjectArray Temp_BBList = env->NewObjectArray(tracks[i].traj_size, class_Track_BoundingBox, 0);
    int j = 0;
    printf("J tracks = %d\n", (int) tracks[i].traj_size);
    for (j = 0; j < tracks[i].traj_size; ++j) {
      jobject Temp_BB = env->NewObject(class_Track_BoundingBox, Track_BoundingBox_constructor);
      env->SetIntField(Temp_BB, BB_x_id, tracks[i].location_sequence[j].x);
      env->SetIntField(Temp_BB, BB_y_id, tracks[i].location_sequence[j].y);
      env->SetIntField(Temp_BB, BB_width_id, tracks[i].location_sequence[j].width);
      env->SetIntField(Temp_BB, BB_height_id, tracks[i].location_sequence[j].height);
      jbyteArray
          jba = env->NewByteArray(tracks[i].location_sequence[j].width * tracks[i].location_sequence[j].height * 3);
      env->SetByteArrayRegion(jba,
                              0,
                              tracks[i].location_sequence[j].width * tracks[i].location_sequence[j].height * 3,
                              (jbyte *) tracks[i].location_sequence[j].patch_data);
      env->SetObjectField(Temp_BB, BB_patchData_id, jba);
      env->SetObjectArrayElement(Temp_BBList, j, Temp_BB);
      //TODO: release jbyteArray:jba and jobject:Temp_BB
      //env->DeleteLocalRef(jba);
      //env->DeleteLocalRef(Temp_BB);
      //printf("j=%d\n",j);
    }
    //printf("Finished 1\n");
    env->SetObjectField(Temp_Tracks, locationSequence_id, Temp_BBList);
    env->SetObjectArrayElement(Return_TracksList, i, Temp_Tracks);
    //TODO: release jbyte:Temp_Tracks and jbyteArray: Temp_BBList
    //env->DeleteLocalRef(Temp_Tracks);
    //env->DeleteLocalRef(Temp_BBList);
    //printf("Finished 2\n");

  }
  printf("Return\n");
  return Return_TracksList;

}
