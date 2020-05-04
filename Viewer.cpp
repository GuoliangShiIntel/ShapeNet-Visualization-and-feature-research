#include <pcl/point_cloud.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/passthrough.h>
#include <iostream>
#include <string>
#include <thread>
#include <pcl/common/common_headers.h>
#include <pcl/features/normal_3d.h>
#include <pcl/visualization/pcl_visualizer.h>

using namespace pcl;
using namespace std;


int main(int argc, char** argv)
{
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud1(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud2(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud3(new pcl::PointCloud<pcl::PointXYZRGB>);
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud4(new pcl::PointCloud<pcl::PointXYZRGB>);

	int  input_path;
	cout << "Input film path: ";
	cin>>input_path;
	string path1 = "C:/Users/13427/Desktop/ShapeNet可视化与特性研究/shape_" + to_string(input_path) + ".pcd";
	string path2 = "C:/Users/13427/Desktop/ShapeNet可视化与特性研究/shape_" + to_string(input_path+1) + ".pcd";
	string path3 = "C:/Users/13427/Desktop/ShapeNet可视化与特性研究/shape_" + to_string(input_path+2) + ".pcd";
	string path4 = "C:/Users/13427/Desktop/ShapeNet可视化与特性研究/shape_" + to_string(input_path+3) + ".pcd";
	pcl::io::loadPCDFile(path1, *cloud1);
	pcl::io::loadPCDFile(path2, *cloud2);
	pcl::io::loadPCDFile(path3, *cloud3);
	pcl::io::loadPCDFile(path4, *cloud4);

	//创建3D窗口并添加显示点云其包括法线
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer(new pcl::visualization::PCLVisualizer("3D Viewer"));
	viewer->initCameraParameters();
	int v1(0);
	viewer->createViewPort(0.0, 0.0, 0.5, 0.5, v1);
	viewer->setBackgroundColor(1, 1, 1, v1);
	//viewer->addText("Get the stem", 10, 10, "v1 text", v1);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb1(cloud3);
	viewer->addPointCloud<pcl::PointXYZRGB>(cloud3, rgb1, "sample cloud1", v1);
	viewer->addCube(-1, 1, -1, 1, -1, 1, 1, 0, 0, "cube1");
	viewer->setRepresentationToWireframeForAllActors();
	int v2(0);
	viewer->createViewPort(0.5, 0.0, 1.0, 0.5, v2);
	viewer->setBackgroundColor(1.0, 1.0, 1.0, v2);
	//viewer->addText("Plant leaf", 10, 10, "v2 text", v2);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb2(cloud4);
	viewer->addPointCloud<pcl::PointXYZRGB>(cloud4, rgb2, "sample cloud2", v2);
	viewer->addCube(-1, 1, -1, 1, -1, 1, 1, 0, 0, "cube2");
	viewer->setRepresentationToWireframeForAllActors();
	int v3(0);
	viewer->createViewPort(0.0, 0.5, 0.5, 1.0, v3);
	viewer->setBackgroundColor(1, 1, 1, v3);
	//viewer->addText("The original point cloud", 10, 10, "v3 text", v3);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb3(cloud1);
	viewer->addPointCloud<pcl::PointXYZRGB>(cloud1, rgb3, "sample cloud3", v3);
	viewer->addCube(-1, 1, -1, 1, -1, 1, 1, 0, 0, "cube3");
	viewer->setRepresentationToWireframeForAllActors();
	int v4(0);
	viewer->createViewPort(0.5, 0.5, 1.0, 1.0, v4);
	viewer->setBackgroundColor(1, 1, 1, v4);
	//viewer->addText("Euclidean clustering segmentation point cloud", 10, 10, "v4 text", v4);
	pcl::visualization::PointCloudColorHandlerRGBField<pcl::PointXYZRGB> rgb4(cloud2);
	viewer->addPointCloud<pcl::PointXYZRGB>(cloud2, rgb4, "sample cloud4", v4);
	viewer->addCube(-1, 1, -1, 1, -1, 1, 1, 0, 0, "cube4");
	viewer->setRepresentationToWireframeForAllActors();

	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud1");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud2");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 4, "sample cloud3");
	viewer->setPointCloudRenderingProperties(pcl::visualization::PCL_VISUALIZER_POINT_SIZE, 3, "sample cloud4");
	viewer->addCoordinateSystem(0.4);
	while (!viewer->wasStopped())
	{
		viewer->spinOnce(100);
		boost::this_thread::sleep(boost::posix_time::microseconds(100000));
	}
	return (0);
}