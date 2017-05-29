#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat filtrarObjetos(Mat original, Mat filtrada);
bool esLapiz(double momentArea);
bool esCelular(double momentArea);
double hu[7];

//Programa principal
int main() {
	VideoCapture c;
	c.open(0);
	if (!c.isOpened()) {
		cout << "Error al tratar de inicializar la camara" << endl;
	}
	else {
		Mat frame;
		Mat frameHSV;
		Mat frameBlur;
		namedWindow("Original", 1);
		moveWindow("Original", 50, 100);
		namedWindow("Filtrado", 1);
		moveWindow("Filtrado", 700, 100);

		Mat frameMorph;
		while (true) {
			c >> frame;

			cvtColor(frame, frameHSV, CV_BGR2GRAY);
			blur(frameHSV, frameBlur, Size(3, 3));

			//threshold(frameBlur, frameMorph, 180, 255, CV_THRESH_OTSU);
			threshold(frameBlur, frameMorph, 180, 255, 3);

			imshow("Filtrado", frameMorph);

			frame = filtrarObjetos(frame, frameMorph);
			imshow("Original", frame);
			if (waitKey(30) >= 0) {
				break;
			}
		}
		c.release();
	}
	destroyAllWindows();
	return 1;
}

//Método para saber si lo identificado es un lápiz
bool esLapiz(double momentArea, double hu0, double hu1, double hu2, double hu3,
	double hu4, double hu5, double hu6, double hu7) {
	if (momentArea > 4000 && momentArea < 15000 && hu1 > 0.6 && hu1 < 1.4 &&
		hu2 > -0.000 && hu2 < 0.007)
		return true;
	else
		return false;
}

//Método para saber si lo identificado es un celular
bool esCelular(double momentArea, double hu0, double hu1, double hu2,
	double hu3, double hu4, double hu5, double hu6, double hu7) {
	if (momentArea > 40000 && momentArea < 100000 && hu1 > 0.0110 &&
		hu1 < 0.0155 && hu2 > -6.8e-05 && hu2 < 1.7)
		return true;
	else
		return false;
}

//Método para identificar todos los objetos umbralizados y mostrar su contorno
//en la imagen original
Mat filtrarObjetos(Mat original, Mat filtrada) {
	Mat frame = original.clone();
	vector<vector<Point> > contornos;
	vector<Vec4i> jerarquia;
	Scalar color;
	findContours(filtrada, contornos, jerarquia, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	vector<Moments>momentos(contornos.size());
	Point2f centro, centroObjeto;
	Point2f centro0, centro1, centro2, centro3;
	Point2f	centro4, centro5, centro6, centro7;

	cv::Moments mom;
	for (int i = 0; i < contornos.size(); i++) {
		momentos[i] = moments(contornos[i], false);

		mom = cv::moments(contornos[i]);
		HuMoments(mom, hu);

		if (momentos[i].m00>4000 && momentos[i].m00<100000) {
			centro = Point2f(momentos[i].m10 / momentos[i].m00,
				momentos[i].m01 / momentos[i].m00);

			centroObjeto = Point2f(momentos[i].m10 / momentos[i].m00,
				momentos[i].m01 / momentos[i].m00 + 15);

			color = Scalar(0, 255, 0);
			drawContours(frame, contornos, i, color, 2, 8, jerarquia, 0, Point());
			circle(frame, centro, 4, color, -1, 8, 0);
			ostringstream area;
			ostringstream area0, area1, area2, area3;
			ostringstream area4, area5, area6, area7;

			//Imprime las áreas de los objetos identificados
			area << "Area(" << momentos[i].m00 << ")";

			Scalar colorText = Scalar(0, 0, 255);
			putText(frame, area.str(), centro, FONT_HERSHEY_PLAIN, 1,
				colorText, 1, 50);

			//Llamada al método para imprimir si es un lápiz con base a sus 
			//momentos de Hu y el área
			if (esLapiz(momentos[i].m00, hu[0], hu[1], hu[2], hu[3], hu[4],
				hu[5], hu[6], hu[7])) {
				putText(frame, "ES UN LAPIZ", centroObjeto, FONT_HERSHEY_PLAIN,
					1, Scalar(0, 0, 255), 1, 100);
			}

			//Llamada al método para imprimir si es un celular con base a sus
			//momentos de Hu y el área
			if (esCelular(momentos[i].m00, hu[0], hu[1], hu[2], hu[3], hu[4],
				hu[5], hu[6], hu[7])) {
				putText(frame, "ES UN CELULAR", centroObjeto, FONT_HERSHEY_PLAIN,
					1, Scalar(0, 0, 255), 1, 100);
			}
		}
	}
	return frame;
}