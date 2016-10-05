/**@file    basic_define.h
 * @brief   Basic definitions for object tracking.
 * @version 0.3.1   2016/09/20,   0.3.2   2016/09/21
 *          Mainly modify vector to array; and delete member of 'video_url'. 
 * @email   da.li@cripac.ia.ac.cn
 *
 * Licensed under The MIT License [see LICENSE for details]
 */

#ifndef _BASIC_DEFINE_H_
#define _BASIC_DEFINE_H_

// #include <vector>
// #include <string>
// using namespace std;

#define VIDEO_URL_LEN 2048

/**
 * @struct BoundingBox.
 * @brief Bounding box of a pedestrian.
 * Each bounding box represents the location as well as the size
 * of a pedestrian in a frame.
 */
typedef struct _bbox_t {
  int x;   // Left
  int y;   // Top
  int width;
  int height;
  unsigned char *patch_data;
} BoundingBox;

/**
 * @struct Tracklet
 * @brief Tracklet of a target pedestrian.
 * A tracklet represents a series of appears of a target pedestrian
 * in a video.
 */
typedef struct _tracklet_t {
  int tracklet_len;
  int start_frame_idx;
  // BBList location_sequence;
  BoundingBox *location_sequence;
} Tracklet;

#endif // _BASIC_DEFINE_H_
