#include "Image.hpp"
#include "filter.hpp"

int main()
{
	Image image("before.png");
	cv::imshow("before.png", image.getimage());

	// auto median_res_3=image.median(3);
	// median_res_3->show("median_res_3");
	median_filter mf(3);
	mf.filtering(image)->show("median_res_3_2");

	average_filter af(3);
	af.filtering(image)->show("average_res_3_2");

	gauss_filter gf(3,0.8);
	gf.filtering(image)->show("gauss_res_3_0.8_2");

	//image.gauss();
	cv::waitKey(0);
	return 0;
}

// v2_test




// bug change