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

typedef struct _bb_t {
  int x;   // Left
  int y;   // Top
  int width;
  int height;
  unsigned char *patch_data;
} BoundingBox;

// typedef vector<BoundingBox> BBList;

typedef struct _trajectory_t {
  int id;              // It is only unique inside one video.
  int traj_size;
  // string video_url;
  char video_url[VIDEO_URL_LEN];
  int start_frame_idx;
  // BBList location_sequence;
  BoundingBox *location_sequence;
} Trajectory;

// typedef vector<Track> TrackList;

#endif // _BASIC_DEFINE_H_
