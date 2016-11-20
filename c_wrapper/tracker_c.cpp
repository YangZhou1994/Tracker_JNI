//
// Created by ken.yu on 16-11-20.
//

#include <cstring>
#include "ObjTracking.hpp"

extern "C" {
ObjTracking *
init(int width,
     int height,
     int num_channels,
     const unsigned char *conf,
     size_t conf_len) {
  // Initialize a tracker with bytes of the given configuration file.
  ObjTracking *tracker = new ObjTracking;
  int res = tracker->init(width, height, num_channels, (const char *) conf, conf_len);

  if (!res) {
    fprintf(stderr, "Error: The tracker initialization FAILED!\n");
    return NULL;
  } else {
    return tracker;
  }
}

int
feedFrame(ObjTracking *tracker,
          const unsigned char *frame) {
  int res = tracker->doTrack(frame);
  if (!res)
    return -1;
  return 0;
}

int
getTargets(ObjTracking *tracker,
           Trajectory *trajectories) {
  int num_tracklets = 0;
  Trajectory *tracklets = tracker->getTrajs(num_tracklets);
  if (trajectories == NULL)
    return num_tracklets;
  else {
    memcpy(trajectories, tracklets, sizeof(Trajectory) * num_tracklets);
    return 0;
  }
}

void
free(ObjTracking *tracker) {
  delete tracker;
}
}