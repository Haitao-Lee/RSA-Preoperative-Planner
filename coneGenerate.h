#pragma once
#ifndef CONEDATAGENERATE_H
#define CONEDATAGENERATE_H
//#include <vtkAutoInit.h>
//VTK_MODULE_INIT(vtkRenderingOpenGL2);
//VTK_MODULE_INIT(vtkRenderingFreeType);
//VTK_MODULE_INIT(vtkInteractionStyle);
#include "vtkVolume16Reader.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkMarchingCubes.h"
#include "vtkStripper.h"
#include "vtkActor.h"
#include "vtkPolyDataMapper.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "vtkPolyData.h"
#include <iostream>
#include "vtkContourFilter.h"
#include "vtkPolyDataWriter.h"
#include "vtkSTLWriter.h"
#include "vtkDICOMImageReader.h"
#include "vtkOBJExporter.h"
#include <vtkCoordinate.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkImageData.h>
#include <vtkPolyDataNormals.h>
#include <vtkPointData.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkSphereSource.h>
#include <vtkPointPicker.h>
#include <vtkRendererCollection.h>
#include <vtkObjectFactory.h>
#include <vtkProperty.h>
#include <vtkPolyDataMapper.h>
#include <vtkArrowSource.h>
#include <vtkUnstructuredGridReader.h>
#include <vtkSmartPointer.h>
#include <vtkImageCast.h>
#include <vtkMaskPoints.h>
#include <vtkGlyph3D.h>
#include <vtkSmoothPolyDataFilter.h>
#include <vtkConeSource.h>
#include <vtkPlaneSource.h>
#include <vtkLineSource.h>
#include "pointStore.h"

/**********************************************************************************************************************************

data of prothesis:

--distance between 2 screws;12.8mm
--radius of the base 13mm
--prothesis - 模型.stp-1 8.stp-1.STL        screw_apex[3] = {10.1845 7.67663 14.14}       tail_point[3] = {49.1572 7.67591 13.8391}
--prothesis - 模型.stp-1 8.stp-2.STL        screw_apex[3] = {10.1845 20.4766 14.14}       tail_point[3] = {48.9407 20.8844 14.3677}
--prothesis - 模型.stp-1 02.stp-1.STL   middle_screw_apex = {14.0845 14.0766 14.14}       tail_point[3] = {28.2729 14.0766 14.14}

************************************************************************************************************************************/



vtkPoints* coneGenerate(double screwApex[3], double normal[3], double screwLen, int resolution[3], double angleOfDegree, vtkRenderer* Render)
{

	vtkMath::Normalize(normal);
	vtkSmartPointer<vtkConeSource> cone =
		vtkSmartPointer<vtkConeSource>::New();
	cone->SetHeight(screwLen);
	cone->SetResolution(100);
	cone->SetDirection(normal);

	double ag = angleOfDegree;
	//std::cout << "angle:" << ag << std::endl;
	double height = cone->GetHeight();
	cone->SetRadius(height * tan(ag * acos(-1) / 180));
	double radius = cone->GetRadius();

	/*double screwLen = 0;
	std::cout << "请输入螺钉长度：";
	std::cin >> screwLen;
	std::cout << std::endl;*/

	double center[3] = { screwApex[0] + normal[0] * screwLen / 2,screwApex[1] + normal[1] * screwLen / 2,screwApex[2] + normal[2] * screwLen / 2 };
	cone->SetCenter(center);
	cone->Update();
	double baseCenter[3] = { screwApex[0] + normal[0] * screwLen ,screwApex[1] + normal[1] * screwLen ,screwApex[2] + normal[2] * screwLen  };
	//int numOfPoint = cone->GetOutput()->GetNumberOfPoints();
	//int numOfLine = cone->GetOutput()->GetNumberOfLines();
	//double* normal = cone->GetDirection();
	//double sum = sqrt(pow(normal[0], 2) + pow(normal[1], 2) + pow(normal[2], 2));
	//std::cout << normal[0] << normal[1] << normal[2] << std::endl;
	//double apex[3] = { 0 };
	//double baseCenter[3] = { 0 };
	//for (int i = 0;i < 3;i++)
	//{
	//	center[i] = cone->GetCenter()[i];
	//	normal[i] = normal[i] / sum;
	//	apex[i] = center[i] + normal[i] * (cone->GetHeight()) / 2;
	//	//std::cout << "apex[i]:" << apex[i] << std::endl;
	//	baseCenter[i] = center[i] - normal[i] * (cone->GetHeight()) / 2;
	//	//std::cout << "baseCenter[i]:" << baseCenter[i] << std::endl;
	//}

	vtkSmartPointer<vtkPoints> p =
		vtkSmartPointer<vtkPoints>::New();

	vtkSmartPointer<vtkCellArray> vertices =
		vtkSmartPointer<vtkCellArray>::New();

	vtkIdType pid[1] = { p->InsertNextPoint(screwApex) };
	vertices->InsertNextCell(1, pid);
	pid[0] = p->InsertNextPoint(baseCenter);
	vertices->InsertNextCell(1, pid);
	//pid[0] = p->InsertNextPoint(center);
	//vertices->InsertNextCell(1, pid);


	vtkSmartPointer<vtkPolyData> PLData =
		vtkSmartPointer<vtkPolyData>::New();

	//vtkSmartPointer<vtkPolyLine> line = 


	vtkSmartPointer<vtkRenderer> ren =
		vtkSmartPointer<vtkRenderer>::New();
	/*double POINT[3][3] = { 0 };
	POINT[0][0] = apex[0];
	POINT[0][1] = apex[1];
	POINT[0][2] = apex[2];

	POINT[1][0] = center[0];
	POINT[1][1] = center[1];
	POINT[1][2] = center[2];

	POINT[2][0] = baseCenter[0];
	POINT[2][1] = baseCenter[1];
	POINT[2][2] = baseCenter[2];*/



	//构造旋转矩阵
	//int resolution[3] = { 0 };
	/*std::cout << "请输入旋转分辨率：";
	std::cin >> resolution[0];
	std::cout << "请输入半径分辨率：";
	std::cin >> resolution[1];
	std::cout << "请输入积分分辨率：";
	std::cin >> resolution[2];*/


	double roll = 2 * acos(-1) / resolution[0];
	//std::cout << cos(90) << std::endl;

	double rotateMatrix[3][3] =
	{ pow(normal[0],2) * (1 - cos(roll)) + cos(roll),normal[0] * normal[1] * (1 - cos(roll)) + normal[2] * sin(roll),normal[0] * normal[2] * (1 - cos(roll)) - normal[1] * sin(roll),

	 normal[0] * normal[1] * (1 - cos(roll)) - normal[2] * sin(roll),pow(normal[1],2) * (1 - cos(roll)) + cos(roll),normal[1] * normal[2] * (1 - cos(roll)) + normal[0] * sin(roll),

	 normal[0] * normal[2] * (1 - cos(roll)) + normal[1] * sin(roll),normal[1] * normal[2] * (1 - cos(roll)) - normal[0] * sin(roll), pow(normal[2],2) * (1 - cos(roll)) + cos(roll) };

	double baseVector[3] = { -normal[2],0,normal[0] };
	///std::cout << baseVector[0] << baseVector[1] << baseVector[2] << std::endl;
	//std::cout << std::endl;
	double baseVectorSum = sqrt(pow(baseVector[0], 2) + pow(baseVector[1], 2) + pow(baseVector[2], 2));


	/*for (int i = 0;i < 3;i++)
	{
		for (int j = 0;j < 3;j++)
		{
			std::cout << rotateMatrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	*/


	for (int i = 0;i < 3;i++)
	{
		baseVector[i] = baseVector[i] / baseVectorSum;
	}

	double newVector[3] = { 0 };
	for (int i = 0;i < resolution[0];i++)
	{
		for (int j = 0;j < 3;j++)
		{

			newVector[j] = baseVector[0] * rotateMatrix[0][j] + baseVector[1] * rotateMatrix[1][j] + baseVector[2] * rotateMatrix[2][j];
			//std::cout << "baseVector[" << j << "]:" << baseVector[j] << std::endl;

		}
		baseVector[0] = newVector[0];
		baseVector[1] = newVector[1];
		baseVector[2] = newVector[2];
		//double newPoint[3] = { baseCenter[0] + baseVector[0] * radius,baseCenter[1]+baseVector[1] * radius ,baseCenter[2] +baseVector[2]* radius };
		//p->InsertNextPoint(newPoint);


		for (int k = 1;k < resolution[1] + 1;k++)
		{
			double rate = double(k) / double(resolution[1]);
			//std::cout << "rate:" << rate << std::endl;
			double radiusNewPoint[3] = { baseCenter[0] + baseVector[0] * radius * rate,baseCenter[1] + baseVector[1] * radius * rate ,baseCenter[2] + baseVector[2] * radius * rate };
			p->InsertNextPoint(radiusNewPoint);

			vtkSmartPointer<vtkLineSource> lineSource =
				vtkSmartPointer<vtkLineSource>::New();
			lineSource->SetPoint1(screwApex);
			lineSource->SetPoint2(radiusNewPoint);
			lineSource->Update();

			vtkSmartPointer<vtkPolyDataMapper>lineMapper =
				vtkSmartPointer<vtkPolyDataMapper>::New();
			lineMapper->SetInputConnection(lineSource->GetOutputPort());

			vtkSmartPointer<vtkActor> actorLine =
				vtkSmartPointer<vtkActor>::New();
			actorLine->SetMapper(lineMapper);
			actorLine->GetProperty()->SetColor(0, 0, 1);
			actorLine->GetProperty()->SetLineWidth(5 * acos(-1) / resolution[0]);

			ren->AddActor(actorLine);

			for (int t = 0;t < resolution[2];t++)
			{
				double apexVector[3] = { radiusNewPoint[0] - screwApex[0],radiusNewPoint[1] - screwApex[1], radiusNewPoint[2] - screwApex[2] };
				double apexVectorSum = sqrt(pow(apexVector[0], 2)+ pow(apexVector[1], 2)+ pow(apexVector[2], 2));
				apexVector[0] = apexVector[0] / apexVectorSum;
				apexVector[1] = apexVector[1] / apexVectorSum;
				apexVector[2] = apexVector[2] / apexVectorSum;

				double screwLen = apexVectorSum;
				double calPoint[3] =
				{ screwApex[0] + apexVector[0] * screwLen * t / resolution[2],
				  screwApex[1] + apexVector[1] * screwLen * t / resolution[2],
				  screwApex[2] + apexVector[2] * screwLen * t / resolution[2] };
				p->InsertNextPoint(calPoint);
			}
			//std::cout << "radiusNewPoint: " << radiusNewPoint[0] << " " << radiusNewPoint[1] << " " << radiusNewPoint[2] << std::endl;
		}
	}



	int numOfPoint = resolution[0] * resolution[1] + 2;
	//std::cout << numOfPoint <<" "<< numOfLine << std::endl;
	for (int i = 0;i < numOfPoint;i++)
	{
		vtkSmartPointer<vtkPolyDataMapper>PointMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();

		vtkSmartPointer<vtkSphereSource> sphere =
			vtkSmartPointer<vtkSphereSource>::New();
		sphere->SetCenter(p->GetPoint(i));
		//std::cout << "POINT[i]:" << POINT[i][0] << ',' << POINT[i][1] << ',' << POINT[i][2] << std::endl;
		sphere->SetRadius(0.2 * acos(-1) / resolution[0]);
		sphere->SetPhiResolution(10);
		sphere->SetThetaResolution(10);

		PointMapper->SetInputConnection(sphere->GetOutputPort());

		vtkSmartPointer<vtkActor> actorPoint =
			vtkSmartPointer<vtkActor>::New();
		actorPoint->SetMapper(PointMapper);
		actorPoint->GetProperty()->SetColor(0, 1.0, 0);
		//std::cout << "drawing sphere " << i << std::endl;
		ren->AddActor(actorPoint);
	}

	/*vtkSmartPointer<vtkSphereSource> sphereCenter =
		vtkSmartPointer<vtkSphereSource>::New();
	sphereCenter->SetCenter(center);
	sphereCenter->SetRadius(0.2 / resolution);
	sphereCenter->SetPhiResolution(10);
	sphereCenter->SetThetaResolution(10);


	vtkSmartPointer<vtkPolyDataMapper>PointMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	PointMapper->SetInputConnection(sphereCenter->GetOutputPort());

	vtkSmartPointer<vtkActor> actorPoint =
		vtkSmartPointer<vtkActor>::New();
	actorPoint->SetMapper(PointMapper);
	actorPoint->SetMapper(PointMapper);
	actorPoint->GetProperty()->SetColor(0, 1.0, 0);
	ren->AddActor(actorPoint);*/

	vtkSmartPointer<vtkPolyDataMapper>coneMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	coneMapper->SetInputConnection(cone->GetOutputPort());

	vtkSmartPointer<vtkActor> actorCone =
		vtkSmartPointer<vtkActor>::New();
	actorCone->SetMapper(coneMapper);
	actorCone->GetProperty()->SetColor(1.0, 0.0, 0.0);
	actorCone->GetProperty()->SetOpacity(0.5);
	ren->AddActor(actorCone);

	vtkSmartPointer<vtkLineSource> lineSource =
		vtkSmartPointer<vtkLineSource>::New();
	lineSource->SetPoint1(screwApex);
	lineSource->SetPoint2(baseCenter);
	lineSource->Update();

	vtkSmartPointer<vtkPolyDataMapper>lineMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	lineMapper->SetInputConnection(lineSource->GetOutputPort());

	vtkSmartPointer<vtkActor> actorLine =
		vtkSmartPointer<vtkActor>::New();
	actorLine->SetMapper(lineMapper);
	actorLine->GetProperty()->SetColor(0, 0, 1);
	actorLine->GetProperty()->SetLineWidth(2 * acos(-1) / resolution[0]);
	ren->AddActor(actorLine);

	vtkSmartPointer<vtkRenderWindow> renWin =
		vtkSmartPointer<vtkRenderWindow>::New();
	renWin->AddRenderer(ren);
	renWin->Render();


	vtkSmartPointer<vtkRenderWindowInteractor> RWInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();

	vtkSmartPointer<vtkInteractorStyleTrackballCamera> interStyle =
		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	RWInteractor->SetInteractorStyle(interStyle);

	RWInteractor->SetRenderWindow(renWin);

	RWInteractor->Initialize();
	RWInteractor->Start();

	return p;

}
//{
//	vtkSmartPointer<vtkConeSource> cone =
//		vtkSmartPointer<vtkConeSource>::New();
//	cone->SetHeight(10);
//	cone->SetResolution(100);
//	double ag = 0;
//	std::cout << "请输入角度约束：";
//	std::cin >> ag;
//	std::cout << std::endl;
//	//std::cout << "angle:" << ag << std::endl;
//	double height = cone->GetHeight();
//	cone->SetRadius(height * tan(ag * acos(-1) / 180));
//	double radius = cone->GetRadius();
//
//	/*double screwLen = 0;
//	std::cout << "请输入螺钉长度：";
//	std::cin >> screwLen;
//	std::cout << std::endl;*/
//
//	double center[3] = { 0 };
//	//int numOfPoint = cone->GetOutput()->GetNumberOfPoints();
//	int numOfLine = cone->GetOutput()->GetNumberOfLines();
//	double* normal = cone->GetDirection();
//	double sum = sqrt(pow(normal[0], 2) + pow(normal[1], 2) + pow(normal[2], 2));
//	//std::cout << normal[0] << normal[1] << normal[2] << std::endl;
//	double apex[3] = { 0 };
//	double baseCenter[3] = { 0 };
//	for (int i = 0;i < 3;i++)
//	{
//		center[i] = cone->GetCenter()[i];
//		normal[i] = normal[i] / sum;
//		apex[i] = center[i] + normal[i] * (cone->GetHeight()) / 2;
//		//std::cout << "apex[i]:" << apex[i] << std::endl;
//		baseCenter[i] = center[i] - normal[i] * (cone->GetHeight()) / 2;
//		//std::cout << "baseCenter[i]:" << baseCenter[i] << std::endl;
//	}
//
//	vtkSmartPointer<vtkPoints> p =
//		vtkSmartPointer<vtkPoints>::New();
//
//	vtkSmartPointer<vtkCellArray> vertices =
//		vtkSmartPointer<vtkCellArray>::New();
//
//	vtkIdType pid[1] = { p->InsertNextPoint(apex) };
//	vertices->InsertNextCell(1, pid);
//	pid[0] = p->InsertNextPoint(baseCenter);
//	vertices->InsertNextCell(1, pid);
//	//pid[0] = p->InsertNextPoint(center);
//	//vertices->InsertNextCell(1, pid);
//
//
//	vtkSmartPointer<vtkPolyData> PLData =
//		vtkSmartPointer<vtkPolyData>::New();
//
//	//vtkSmartPointer<vtkPolyLine> line = 
//
//
//	vtkSmartPointer<vtkRenderer> ren =
//		vtkSmartPointer<vtkRenderer>::New();
//	/*double POINT[3][3] = { 0 };
//	POINT[0][0] = apex[0];
//	POINT[0][1] = apex[1];
//	POINT[0][2] = apex[2];
//
//	POINT[1][0] = center[0];
//	POINT[1][1] = center[1];
//	POINT[1][2] = center[2];
//
//	POINT[2][0] = baseCenter[0];
//	POINT[2][1] = baseCenter[1];
//	POINT[2][2] = baseCenter[2];*/
//
//
//
//	//构造旋转矩阵
//	int resolution[3] = { 0 };
//	std::cout << "请输入旋转分辨率：";
//	std::cin >> resolution[0];
//	std::cout << "请输入半径分辨率：";
//	std::cin >> resolution[1];
//	std::cout << "请输入积分分辨率：";
//	std::cin >> resolution[2];
//
//
//	double roll = 2 * acos(-1) / resolution[0];
//	//std::cout << cos(90) << std::endl;
//
//	double rotateMatrix[3][3] =
//	{ pow(normal[0],2) * (1 - cos(roll)) + cos(roll),normal[0] * normal[1] * (1 - cos(roll)) + normal[2] * sin(roll),normal[0] * normal[2] * (1 - cos(roll)) - normal[1] * sin(roll),
//
//	 normal[0] * normal[1] * (1 - cos(roll)) - normal[2] * sin(roll),pow(normal[1],2) * (1 - cos(roll)) + cos(roll),normal[1] * normal[2] * (1 - cos(roll)) + normal[0] * sin(roll),
//
//	 normal[0] * normal[2] * (1 - cos(roll)) + normal[1] * sin(roll),normal[1] * normal[2] * (1 - cos(roll)) - normal[0] * sin(roll), pow(normal[2],2) * (1 - cos(roll)) + cos(roll) };
//
//	double baseVector[3] = { -normal[2],0,normal[0] };
//	///std::cout << baseVector[0] << baseVector[1] << baseVector[2] << std::endl;
//	//std::cout << std::endl;
//	double baseVectorSum = sqrt(pow(baseVector[0], 2) + pow(baseVector[1], 2) + pow(baseVector[2], 2));
//
//
//	/*for (int i = 0;i < 3;i++)
//	{
//		for (int j = 0;j < 3;j++)
//		{
//			std::cout << rotateMatrix[i][j] << " ";
//		}
//		std::cout << std::endl;
//	}
//	std::cout << std::endl;
//	*/
//
//
//	for (int i = 0;i < 3;i++)
//	{
//		baseVector[i] = baseVector[i] / baseVectorSum;
//	}
//
//	double newVector[3] = { 0 };
//	for (int i = 0;i < resolution[0];i++)
//	{
//		for (int j = 0;j < 3;j++)
//		{
//
//			newVector[j] = baseVector[0] * rotateMatrix[0][j] + baseVector[1] * rotateMatrix[1][j] + baseVector[2] * rotateMatrix[2][j];
//			//std::cout << "baseVector[" << j << "]:" << baseVector[j] << std::endl;
//
//		}
//		baseVector[0] = newVector[0];
//		baseVector[1] = newVector[1];
//		baseVector[2] = newVector[2];
//		//double newPoint[3] = { baseCenter[0] + baseVector[0] * radius,baseCenter[1]+baseVector[1] * radius ,baseCenter[2] +baseVector[2]* radius };
//		//p->InsertNextPoint(newPoint);
//
//
//		for (int k = 1;k < resolution[1] + 1;k++)
//		{
//			double rate = double(k) / double(resolution[1]);
//			//std::cout << "rate:" << rate << std::endl;
//			double radiusNewPoint[3] = { baseCenter[0] + baseVector[0] * radius * rate,baseCenter[1] + baseVector[1] * radius * rate ,baseCenter[2] + baseVector[2] * radius * rate };
//			p->InsertNextPoint(radiusNewPoint);
//
//			vtkSmartPointer<vtkLineSource> lineSource =
//				vtkSmartPointer<vtkLineSource>::New();
//			lineSource->SetPoint1(apex);
//			lineSource->SetPoint2(radiusNewPoint);
//			lineSource->Update();
//
//			vtkSmartPointer<vtkPolyDataMapper>lineMapper =
//				vtkSmartPointer<vtkPolyDataMapper>::New();
//			lineMapper->SetInputConnection(lineSource->GetOutputPort());
//
//			vtkSmartPointer<vtkActor> actorLine =
//				vtkSmartPointer<vtkActor>::New();
//			actorLine->SetMapper(lineMapper);
//			actorLine->GetProperty()->SetColor(0, 0, 1);
//			actorLine->GetProperty()->SetLineWidth(5 * acos(-1) / resolution[0]);
//
//			ren->AddActor(actorLine);
//
//			/*for (int t = 0;t < resolution[2];t++)
//			{
//				double apexVector[3] = { radiusNewPoint[0] - apex[0],radiusNewPoint[1] - apex[1], radiusNewPoint[2] - apex[2] };
//				double apexVectorSum = sqrt(pow(apexVector[0], 2)+ pow(apexVector[1], 2)+ pow(apexVector[2], 2));
//				apexVector[0] = apexVector[0] / apexVectorSum;
//				apexVector[1] = apexVector[1] / apexVectorSum;
//				apexVector[2] = apexVector[2] / apexVectorSum;
//
//				double screwLen = apexVectorSum;
//				double calPoint[3] =
//				{ apex[0] + apexVector[0] * screwLen * t / resolution[2],
//				  apex[1] + apexVector[1] * screwLen * t / resolution[2],
//				  apex[2] + apexVector[2] * screwLen * t / resolution[2] };
//				p->InsertNextPoint(calPoint);
//			}*/
//			//std::cout << "radiusNewPoint: " << radiusNewPoint[0] << " " << radiusNewPoint[1] << " " << radiusNewPoint[2] << std::endl;
//		}
//	}
//
//
//
//	int numOfPoint = p->GetNumberOfPoints();
//	//std::cout << numOfPoint <<" "<< numOfLine << std::endl;
//	for (int i = 0;i < numOfPoint;i++)
//	{
//		vtkSmartPointer<vtkPolyDataMapper>PointMapper =
//			vtkSmartPointer<vtkPolyDataMapper>::New();
//
//		vtkSmartPointer<vtkSphereSource> sphere =
//			vtkSmartPointer<vtkSphereSource>::New();
//		sphere->SetCenter(p->GetPoint(i));
//		//std::cout << "POINT[i]:" << POINT[i][0] << ',' << POINT[i][1] << ',' << POINT[i][2] << std::endl;
//		sphere->SetRadius(0.2 * acos(-1) / resolution[0]);
//		sphere->SetPhiResolution(10);
//		sphere->SetThetaResolution(10);
//
//		PointMapper->SetInputConnection(sphere->GetOutputPort());
//
//		vtkSmartPointer<vtkActor> actorPoint =
//			vtkSmartPointer<vtkActor>::New();
//		actorPoint->SetMapper(PointMapper);
//		actorPoint->GetProperty()->SetColor(0, 1.0, 0);
//		//std::cout << "drawing sphere " << i << std::endl;
//		ren->AddActor(actorPoint);
//	}
//
//	/*vtkSmartPointer<vtkSphereSource> sphereCenter =
//		vtkSmartPointer<vtkSphereSource>::New();
//	sphereCenter->SetCenter(center);
//	sphereCenter->SetRadius(0.2 / resolution);
//	sphereCenter->SetPhiResolution(10);
//	sphereCenter->SetThetaResolution(10);
//
//
//	vtkSmartPointer<vtkPolyDataMapper>PointMapper =
//		vtkSmartPointer<vtkPolyDataMapper>::New();
//	PointMapper->SetInputConnection(sphereCenter->GetOutputPort());
//
//	vtkSmartPointer<vtkActor> actorPoint =
//		vtkSmartPointer<vtkActor>::New();
//	actorPoint->SetMapper(PointMapper);
//	actorPoint->SetMapper(PointMapper);
//	actorPoint->GetProperty()->SetColor(0, 1.0, 0);
//	ren->AddActor(actorPoint);*/
//
//	vtkSmartPointer<vtkPolyDataMapper>coneMapper =
//		vtkSmartPointer<vtkPolyDataMapper>::New();
//	coneMapper->SetInputConnection(cone->GetOutputPort());
//
//	vtkSmartPointer<vtkActor> actorCone =
//		vtkSmartPointer<vtkActor>::New();
//	actorCone->SetMapper(coneMapper);
//	actorCone->GetProperty()->SetColor(1.0, 0.0, 0.0);
//	actorCone->GetProperty()->SetOpacity(0.5);
//	ren->AddActor(actorCone);
//
//	vtkSmartPointer<vtkLineSource> lineSource =
//		vtkSmartPointer<vtkLineSource>::New();
//	lineSource->SetPoint1(apex);
//	lineSource->SetPoint2(baseCenter);
//	lineSource->Update();
//
//	vtkSmartPointer<vtkPolyDataMapper>lineMapper =
//		vtkSmartPointer<vtkPolyDataMapper>::New();
//	lineMapper->SetInputConnection(lineSource->GetOutputPort());
//
//	vtkSmartPointer<vtkActor> actorLine =
//		vtkSmartPointer<vtkActor>::New();
//	actorLine->SetMapper(lineMapper);
//	actorLine->GetProperty()->SetColor(0, 0, 1);
//	actorLine->GetProperty()->SetLineWidth(2 * acos(-1) / resolution[0]);
//	ren->AddActor(actorLine);
//
//	vtkSmartPointer<vtkRenderWindow> renWin =
//		vtkSmartPointer<vtkRenderWindow>::New();
//	renWin->AddRenderer(ren);
//	renWin->Render();
//
//
//	vtkSmartPointer<vtkRenderWindowInteractor> RWInteractor =
//		vtkSmartPointer<vtkRenderWindowInteractor>::New();
//
//	vtkSmartPointer<vtkInteractorStyleTrackballCamera> interStyle =
//		vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
//	RWInteractor->SetInteractorStyle(interStyle);
//
//	RWInteractor->SetRenderWindow(renWin);
//
//	RWInteractor->Initialize();
//	RWInteractor->Start();
//
//	return EXIT_SUCCESS;

#endif // !CONEDATAGENERATE_H
