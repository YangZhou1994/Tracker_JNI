/**\file    basic_define.h
 * \brief   some basic definitions ...
 * \version 0.3.1   2016/09/20,   0.3.2   2016/09/21
 *          Mainly modify vector to array; and delete member of 'video_url'. 
 * \email   da.li@cripac.ia.ac.cn
 */

#ifndef _BASIC_DEFINE_H_
#define _BASIC_DEFINE_H_

// #include <vector>
// #include <string>
// using namespace std;

#define VIDEO_URL_LEN 2048

typedef struct _bbox_t {
  int x;   // Left
  int y;   // Top
  int width;
  int height;
  unsigned char *patch_data;
} BoundingBox;

// typedef vector<BoundingBox> BBList;

typedef struct _tracklet_t {
  int tracklet_len_;
  int start_frame_idx_;
  // BBList location_sequence;
  BoundingBox *location_sequence;
} Tracklet;

// typedef vector<Track> TrackList;

#endif // _BASIC_DEFINE_H_
