#pragma once
#ifndef POINTSTORE_H
#define POINTSTORE_H
#include <vtkAutoInit.h>
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkRenderingFreeType);
VTK_MODULE_INIT(vtkInteractionStyle);
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
#include <vtkPlaneSource.h>


/**********************************************************************************************************************************

data of prothesis:

--distance between 2 screws;12.8mm
--radius of the base 13mm
--prothesis - 模型.stp-1 8.stp-1.STL        screw_apex[3] = {10.1845 7.67663 14.14}       tail_point[3] = {49.1572 7.67591 13.8391}
--prothesis - 模型.stp-1 8.stp-2.STL        screw_apex[3] = {10.1845 20.4766 14.14}       tail_point[3] = {48.9407 20.8844 14.3677}
--prothesis - 模型.stp-1 02.stp-1.STL   middle_screw_apex = {14.0845 14.0766 14.14}       tail_point[3] = {28.2729 14.0766 14.14}

************************************************************************************************************************************/



class pointStore
{
public:
	int pointNum;
	double point[3];
	//double normal[3];
	pointStore* nextPoint;


	pointStore();
	~pointStore();
	void addPoint(double pick[3]);
	double* getPoint(int rank);
	void deleteLastPoint();
	void printSelf();
	void changePoint(int rank, double* newPoint);
	void clear();

private:
	void deleteAll();
};

#endif