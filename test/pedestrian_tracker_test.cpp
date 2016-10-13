//
// Created by ken.yu on 16-10-6.
//

#include <cerrno>
#include <iostream>
#include <cstdio>

#include <opencv2/opencv.hpp>

#include "ObjTracking.hpp"

#define BUF_SIZE 10000

using namespace cv;
using namespace std;

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: pedestrian_tracker_test path/to/test/video path/to/config/file\n");
    return 1;
  }
  printf("Called with %s %s\n", argv[1], argv[2]);

  VideoCapture cap(argv[1]);

  FILE *conf = fopen(argv[2], "rw");
  char *buf = (char *) malloc(BUF_SIZE);
  int len = fread(buf, 1, BUF_SIZE, conf);
  printf("Read config file with len=%d\n", len);

  Mat frame;
  cap >> frame;
  if (frame.empty()) {
    fprintf(stderr, "Cannot read video %d!\n", argv[1]);
    return 2;
  }
  cap.release();
  fprintf(stdout, "Video opened!\n");

  ObjTracking tracker;
  tracker.init(frame.cols, frame.rows, frame.channels(), buf, len);
  fprintf(stdout, "Tracker initialized!\n");

  while (!frame.empty()) {
    tracker.doTrack(frame.data);
    cap >> frame;
  }

  int num_tracklets;
  Trajectory *tracklets = tracker.getTrajs(num_tracklets);

  // Display
  const char *windowName = "Tracking result";
  cap.open(argv[1]);
  int interval = 900 / cap.get(CV_CAP_PROP_FPS);
  int frame_idx = 0;
  while (true) {
    Mat frame;
    cap >> frame;
    if (frame.empty())
      break;
    for (int i = 0; i < num_tracklets; ++i)
      if (tracklets[i].start_frame_idx <= frame_idx
          && tracklets[i].start_frame_idx + tracklets[i].traj_size > frame_idx) {
        const BoundingBox &bbox = tracklets[i].location_sequence[frame_idx - tracklets[i].start_frame_idx];
        rectangle(frame, Rect(bbox.x, bbox.y, bbox.width, bbox.height), Scalar(255, 0, 0));
      }
    imshow(windowName, frame);
    waitKey(interval);
  }
  destroyWindow(windowName);

  free(buf);

  return 0;
}