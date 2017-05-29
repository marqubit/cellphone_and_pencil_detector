#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace ::cv;
using namespace ::std;

#define LEVEL 1

int main(int argc, char *argv[])
{
	const string root_path = "C:/Users/MarQubit/Pictures/momos/vv.jpg";

	const string in_path = root_path + "000.jpg";
	const Mat in = imread(in_path, CV_LOAD_IMAGE_ANYCOLOR);
	assert(!in.empty());

	const string in_window = "Input";
	imshow(in_window, in);
	waitKey();

	Mat canvas = in.clone();
	const Point up_left(480, 70);
	const Point bottom_right(520, 150);
	const Scalar line_color(0, 255, 255);
	const int thickness = 3;
	rectangle(canvas, up_left, bottom_right, line_color, thickness);

#if LEVEL == 1
	const string canvas_window = "Canvas";
	imshow(canvas_window, canvas);
	waitKey();
#endif

	const Rect roi(up_left, bottom_right);
	const Mat sample = in(roi);

#if LEVEL == 2
	const string sample_window = "Sample";
	imshow(sample_window, sample);
	waitKey();

	const string sample_path = root_path + "000-sample.jpg";
	imwrite(sample_path, sample);
#endif

	Scalar sample_mean;
	Scalar sample_standard_deviation;
	meanStdDev(sample, sample_mean, sample_standard_deviation);

#if LEVEL == 3
	cout << "Mean: " << sample_mean << endl
		<< "Standard deviation: " << sample_standard_deviation << endl;
#endif

	const float alpha = 2.0;
	const Scalar lower_bound = sample_mean - alpha * sample_standard_deviation;
	const Scalar upper_bound = sample_mean + alpha * sample_standard_deviation;

	Mat out;
	inRange(in, lower_bound, upper_bound, out);

#if LEVEL == 4
	const string out_window = "Out";
	imshow(out_window, out);
	waitKey();

	const string out_path = root_path + "000-out.jpg";
	imwrite(out_path, out);
#endif
}
