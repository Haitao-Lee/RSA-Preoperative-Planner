#pragma once
#pragma once
#ifndef POINTPICKERINTETACTORSTYLE_H
#define POINTPICKERINTETACTORSTYLE_H
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
#include <vtkPlaneSource.h>
#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkPropPicker.h>
#include <vtkPointData.h>
#include <vtkCylinderSource.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkMinimalStandardRandomSequence.h>
#include <vtkTransform.h>
#include <vtkMatrix4x4.h>
#include <vtkLineSource.h>
#include <vtkTubeFilter.h>
#include <vtkActorCollection.h>
#include <vtkPlaneCollection.h>
#include <vtkPlane.h>
#include <vtkCellPicker.h>
#include <vtkAlgorithmOutput.h>
#include <conio.h>
#include <vtkClipPolyData.h>
#include <itkVTKImageToImageFilter.h>
#include <itkImageToVTKImageFilter.h>
#include <vtkMarchingCubes.h>
#include <vtkPointSet.h>
#include "pointStore.h"
#include  "myReslice.h"
#include <qprogressbar.h>
#include <QtWidgets\qplaintextedit.h>


/**********************************************************************************************************************************

data of prosthesis:

--radius of screw: 3.20mm
--distance between 2 screws: 12.8mm
--radius of the base 13mm
--prosthesis - 模型.stp-1 8.stp-1.STL        screw_apex[3] = {10.1845 7.67663 14.14}       tail_point[3] = {49.1572 7.67591 13.8391}
--prosthesis - 模型.stp-1 8.stp-2.STL        screw_apex[3] = {10.1845 20.4766 14.14}       tail_point[3] = {48.9407 20.8844 14.3677}
--prosthesis - 模型.stp-1 02.stp-1.STL   middle_screw_apex = {13.58   14.08   14.14}       tail_point[3] = {28.3    14.08     14.14}

************************************************************************************************************************************/

class vtkImageInteractionCallback;

class PickerInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	pointStore* point;
	vtkSmartPointer<vtkImageData> boneIMGData;
	vtkSmartPointer<vtkPolyData> wholeBonePolyData;
	vtkSmartPointer<vtkPolyData> curBonePolyData;
	vtkSmartPointer<vtkPolyData> base_poly_data;
	vtkSmartPointer<vtkPolyData> screw1_poly_data;
	vtkSmartPointer<vtkPolyData> screw2_poly_data;
	double planeNormal[3];
	vtkSmartPointer<vtkActor> bone_cur_actor;
	vtkSmartPointer<vtkActor> bone_origin_actor;
	vtkSmartPointer<vtkActor> clip_actor1;
	vtkSmartPointer<vtkActor> clip_actor2;
	vtkSmartPointer<vtkActor> plane_actor;
	vtkSmartPointer<vtkActor> middle_point_actor;
	vtkSmartPointer<vtkActor> base_actor;
	vtkSmartPointer<vtkActor> actor_cone1;
	vtkSmartPointer<vtkActor> actor_cone2;
	vtkSmartPointer<vtkActor> screw_actor1;
	vtkSmartPointer<vtkActor> screw_actor2;
	vtkSmartPointer<vtkPolyData> screw_data;
	vtkSmartPointer<vtkPolyData> base_data;
	vtkSmartPointer< vtkImageCast> bone_img_cast;
	vtkSmartPointer< vtkPoints> extract_points;
	itk::SmartPointer<itk::ImageToVTKImageFilter<itk::Image<signed short, 3>>> bone_img_reader;
	//vtkSmartPointer<vtkDICOMImageReader> bone_img_reader;
	vtkSmartPointer<vtkImageInteractionCallback> callback1;
	vtkSmartPointer<vtkImageInteractionCallback> callback2;
	vtkSmartPointer<vtkImageInteractionCallback> callback3;
	vtkSmartPointer<vtkLookupTable>  colorTable;
	vtkSmartPointer<vtkMarchingCubes> boneExtractor;


	float* patient_origin;
	bool planeOrNot;
	bool clippedOrNot;
	bool finish;
	bool segmentOrNot;
	double range[2];
	int pointNum;
	int resolution[3];
	double angleOfDegree;
	vtkSmartPointer<vtkPlane> plane;
	int threshold1;
	int threshold2;
	double screw_radius = 1.89;
	double middle_radius = 3.95;
	double screwLen = 38.97;
	double middleLen = 14.72;
	double distance = 12.97;
	double finalPath[18];
	double bone_center[3];
	double spin_reference_point[3];
	int avail_path;
	double screw_apex1[3];
	double screw_apex2[3];
	double screw_apex_offset;
	double threshold_offset;
	QPlainTextEdit* text_out;
	//QProgressBar* pointPickerBar;

	inline static PickerInteractorStyle* New();
	//virtual void OnRightButtonDown();
	void pointVisualize(int rank);
	void normalVisualize(int rank);
	//double* getPickded();
	void initialize(vtkPolyData* bonePolyData, vtkActor* boneActor, vtkImageData* bone_IMG_data, vtkImageCast* bone_img_cast, vtkPolyData* screw_data, vtkPolyData* base_data, int resolution[3], double  angleOfDegree, double range[2],double bone_center[3], vtkPoints* extract_ps, vtkMarchingCubes* boneExtractor);
	double* getLastPicked();
	double* getPicked(int rank);
	virtual void OnRightButtonDown();
	virtual void OnRightButtonUp();
	virtual void OnLeftButtonDown();
	//virtual void OnLeftButtonUp();
	virtual void OnMouseMove();
	vtkPoints* coneGenerate(double screwApex[3], double normal[3], double screwLen, int resolution[3], double angleOfDegree, double vector[3]);
	double* inPlantPoint(double distance, double middlePoint[3], double reference_point1[3], double reference_point2[3], double screw_apex_offset);
	double* normalInsight(double normal[3], double startPoint[3], vtkImageData* bone_IMG_data, double screwLen);
	double* generatePath(vtkPoints* p, vtkImageData* bone_IMG_Data, double screwLen, int* resolution, int threshold);
	//double* lamda_generatePath(vtkPoints* p, vtkImageData* bone_IMG_Data, double screwLen, int* resolution);
	int CTValueNormalize(double Hu);
	vtkTypeMacro(PickerInteractorStyle, vtkInteractorStyleTrackballCamera);
};
vtkStandardNewMacro(PickerInteractorStyle);

class vtkImageInteractionCallback : public vtkCommand
{
public:
	int Slicing;
	vtkImageReslice* ImageReslice;
	vtkImageMapToColors* MapToColors;
	vtkRenderWindowInteractor* Interactor;
	vtkRenderWindow* RenderWindow;
	vtkImageData* OutputImageData;
	vtkSmartPointer<vtkPolyData> prosthesis_base;
	vtkSmartPointer<vtkPolyData> screw1;
	vtkSmartPointer<vtkPolyData> screw2;
	//vtkSmartPointer<vtkPolyData> screw2;
	vtkSmartPointer<vtkRenderer> contour_renderer;
	vtkSmartPointer<vtkRenderer> image_renderer;
	vtkTypeBool prosthesisOrNot = 0;
	vtkImageData* boneIMGData;
	double offset = 0;
	double zoom_rate = 1.2;
	bool rm_ornot;
	bool text_flag;
	bool img_ornot;
	vtkSmartPointer<vtkCamera> myCamera;
	double change_rate;
	QSlider* slider;
	double raw_img_bound[6];
	double actor_center[3];
	double line_origin[2];
	double last_picked[2];
	bool picked_before;
	double ParallelScale = 120;
	double line_length = 800;
	double line_width = 1;
	vtkSmartPointer<vtkActor> x_line_actor;
	vtkSmartPointer<vtkActor> y_line_actor;
	PickerInteractorStyle* common_style;
	vtkSmartPointer<vtkCellPicker> picker;

	inline static vtkImageInteractionCallback* New();

	vtkImageInteractionCallback();

	void SetImageReslice(vtkImageReslice* reslice);

	void SetMapToColors(vtkImageMapToColors* colors);

	void SetInteractor(vtkRenderWindowInteractor* interactor);

	void SetRenderWindow(vtkRenderWindow* window);

	void Execute(vtkObject* caller, unsigned long eventId, void* callData) override;

	void synWithOtherCallback(double depth);

	void setProsthesis(vtkPolyData* b, vtkPolyData* s1, vtkPolyData* s2, vtkTypeBool flag = 0);

	void setImageData(vtkImageData* boneImgData, double dcm_center[3], vtkRenderer* image_renderer, PickerInteractorStyle* common_style);

	void setSlider(QSlider* slider);

	vtkTypeMacro(vtkImageInteractionCallback, vtkCommand);
};
vtkStandardNewMacro(vtkImageInteractionCallback);
#endif
