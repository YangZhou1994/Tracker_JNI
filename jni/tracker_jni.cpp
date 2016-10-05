/** \file    tracking_jni.cpp
 *  \brief   Implementation of JNI wrapper for object tracking.
 *  \version 0.1
 *  \date    2016-07-26
 *  \email   da.li@cripac.ia.ac.cn kyu_115s@hotmail.com
 *
 * Licensed under The MIT License [see LICENSE for details]
 */

#include <cstdlib>
#include <cstdio>
#include <string>
#include <jni.h>

#include "org_cripac_isee_pedestrian_tracking_ISEEBasicTracker.h"
#include "ObjTracking.hpp"

using namespace std;

/*
 * Class:     org_cripac_isee_pedestrian_tracking_ISEEBasicTracker
 * Method:    initialize
 * Signature: (III[B)J
 */
JNIEXPORT jlong JNICALL Java_org_cripac_isee_pedestrian_tracking_BasicTracker_initialize
    (JNIEnv *env, jobject obj, jint width, jint height, jint num_channels, jbyteArray jbytes_conf) {
  // Get number of bytes of the configuration file.
  jsize buffer_len = (env)->GetArrayLength(jbytes_conf);
  // Create a native buffer for the configuration file.
  jbyte *conf_buffer = new jbyte[buffer_len];
  // Retrieve bytes from Java to local.
  env->GetByteArrayRegion(jbytes_conf, 0, buffer_len, conf_buffer);

  // Initialize a tracker with bytes of the given configuration file.
  ObjTracking *tracker = new ObjTracking;
  int res = tracker->init(width, height, num_channels, (const char *) conf_buffer, buffer_len);
  delete[] conf_buffer;

  if (!res) {
    fprintf(stderr, "Error: The tracker initialization FAILED!\n");
    return (jlong)NULL;
  } else {
    return (jlong)tracker;
  }
}

/*
 * Class:     org_cripac_isee_pedestrian_tracking_ISEEBasicTracker
 * Method:    feedFrame
 * Signature: (J[B)I
 */
JNIEXPORT jint JNICALL Java_org_cripac_isee_pedestrian_tracking_BasicTracker_feedFrame
    (JNIEnv *env, jobject obj, jlong tracker_pointer, jbyteArray j_frame) {
  ObjTracking *tracker = (ObjTracking *) tracker_pointer;
  jsize buffer_len = (env)->GetArrayLength(j_frame);
  jbyte *frame = new jbyte[buffer_len];
  env->GetByteArrayRegion(j_frame, 0, buffer_len, frame);
  int res = tracker->doTrack((const unsigned char *) (frame));
  delete[](frame);
  if (!res) {
    return -1;
  }
  return 0;
}

/*
 * Class:     org_cripac_isee_pedestrian_tracking_ISEEBasicTracker
 * Method:    getTargets
 * Signature: (J)[Lorg/cripac/isee/pedestrian/tracking/Tracklet;
 */
JNIEXPORT jobjectArray JNICALL Java_org_cripac_isee_pedestrian_tracking_BasicTracker_getTargets
    (JNIEnv *env, jobject obj, jlong pointer) {
  // Analyze Trajectory class in Java.
  jclass tracklet_class = env->FindClass("org/cripac/isee/pedestrian/tracking/Tracklet");
  if (tracklet_class == NULL) {
    fprintf(stderr, "Error: Cannot find Java class: org/cripac/isee/pedestrian/tracking/Tracklet");
    return NULL;
  }
  jmethodID tracklet_constructor = env->GetMethodID(tracklet_class, "<init>", "()V");
  jfieldID loc_seq_field =
      env->GetFieldID(tracklet_class,
                      "locationSequence",
                      "[Lorg/cripac/isee/pedestrian/tracking/Tracklet$BoundingBox;");
  jfieldID start_frame_idxfield =
      env->GetFieldID(tracklet_class,
                      "startFrameIndex",
                      "I");

  // Analyze BoundingBox class in Java.
  jclass bbox_class = env->FindClass("org/cripac/isee/pedestrian/tracking/Tracklet$BoundingBox");
  if (bbox_class == NULL) {
    fprintf(stderr, "Error:Can't find Class:org/cripac/isee/pedestrian/tracking/Tracklet$BoundingBox");
    return NULL;
  }
  jmethodID bbox_constructor = env->GetMethodID(bbox_class, "<init>", "()V");
  jfieldID bbox_x_field = env->GetFieldID(bbox_class, "x", "I");
  jfieldID bbox_y_field = env->GetFieldID(bbox_class, "y", "I");
  jfieldID bbox_width_field = env->GetFieldID(bbox_class, "width", "I");
  jfieldID bbox_height_field = env->GetFieldID(bbox_class, "height", "I");
  jfieldID bbox_patch_data_field = env->GetFieldID(bbox_class, "patchData", "[B");

  // Get tracking results.
  ObjTracking *tracker = (ObjTracking *) pointer;
  int num_tracklets = 0;
  Trajectory *tracklets = tracker->getTrajs(num_tracklets);

  // Create Java tracklet array with equal length with local tracklet result list.
  jobjectArray j_tracklets = env->NewObjectArray((jsize) num_tracklets, tracklet_class, NULL);
  // Fill data of native tracklets into the Java array one by one.
  for (int i = 0; i < num_tracklets; ++i) {
    // For current tracklet.
    const Trajectory &tracklet = tracklets[i];
    // Create a Java tracklet.
    jobject j_tracklet = env->NewObject(tracklet_class, tracklet_constructor);

    // Create Java bounding box array with equal length with the length of current tracklet.
    jobjectArray j_bboxes = env->NewObjectArray(tracklet.traj_size, bbox_class, NULL);
    // Fill data of native bounding box into the Java array one by one.
    for (int j = 0; j < tracklet.traj_size; ++j) {
      // Create a Java bounding box.
      jobject j_bbox = env->NewObject(bbox_class, bbox_constructor);
      // Fill the x, y, width, height fields of the bounding box.
      env->SetIntField(j_bbox, bbox_x_field, tracklet.location_sequence[j].x);
      env->SetIntField(j_bbox, bbox_y_field, tracklet.location_sequence[j].y);
      env->SetIntField(j_bbox, bbox_width_field, tracklet.location_sequence[j].width);
      env->SetIntField(j_bbox, bbox_height_field, tracklet.location_sequence[j].height);

      // Fill the patch data field of the bounding box.
      jbyteArray j_patch_data =
          env->NewByteArray(tracklet.location_sequence[j].width * tracklet.location_sequence[j].height * 3);
      env->SetByteArrayRegion(j_patch_data,
                              0,
                              tracklet.location_sequence[j].width * tracklet.location_sequence[j].height * 3,
                              (jbyte *) tracklet.location_sequence[j].patch_data);
      env->SetObjectField(j_bbox, bbox_patch_data_field, j_patch_data);

      // Insert the new bounding box into the Java bounding box array.
      env->SetObjectArrayElement(j_bboxes, j, j_bbox);

      env->DeleteLocalRef(j_patch_data);
      env->DeleteLocalRef(j_bbox);
    }
    // Put the bounding box array to the locationSequence field of the Java tracklet.
    env->SetObjectField(j_tracklet, loc_seq_field, j_bboxes);
    // Set the startFrameIndex field of the Java tracklet.
    env->SetIntField(j_tracklet, start_frame_idxfield, tracklet.start_frame_idx);
    // Insert the new tracklet into the Java tracklet array.
    env->SetObjectArrayElement(j_tracklets, i, j_tracklet);

    env->DeleteLocalRef(j_tracklet);
    env->DeleteLocalRef(j_bboxes);
  }
  return j_tracklets;
}

/*
 * Class:     org_cripac_isee_pedestrian_tracking_ISEEBasicTracker
 * Method:    free
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_org_cripac_isee_pedestrian_tracking_BasicTracker_free
    (JNIEnv *env, jobject obj, jlong p) {
  delete (ObjTracking *)p;
}