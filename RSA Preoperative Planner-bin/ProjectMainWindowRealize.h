#pragma once
#include "ProjectMainWindow.h"
#include <QFileDialog>
#include <QDir>
#include <vtkImageViewer2.h>
#include <QVTKWidget.h>
#include <vtkEventQtSlotConnect.h>
#include <vtkCommand.h>
#include <vtkDICOMImageReader.h>
#include <vtkMarchingCubes.h>
#include <vtkStripper.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include "vtkProperty.h"
#include <vtkRenderWindow.h>
#include <vtkSTLReader.h>
#include <qpushbutton.h>
#include <qdebug.h>
#include <qmenu.h>
#include <qpoint.h>
#include <vtkNamedColors.h>
#include <qspinbox.h>
#include <qthread.h>
#include <qtimer.h>
#include <time.h>
#include <vtkLineSource.h>
#include <qthread.h>
#include <vtkOutputWindow.h>
#include <vtkAxesActor.h>
#include <vtkPolyDataConnectivityFilter.h>
#include <vtkWorldPointPicker.h>
#include <vtkPointSet.h>
#include <vtkPolygon.h>
#include <vtkCellPicker.h>
#include <vtkSurfaceReconstructionFilter.h>
#include <vtkLookupTable.h>
#include <vtkScalarBarActor.h>
#include <vtkCaptionActor2D.h>
#include <vtkAppendPolyData.h>
#include <vtkNamedColors.h>
#include <vtkProperty2D.h>
#include <vtkTextProperty.h>
#include <vtkContourFilter.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkColorTransferFunction.h>
#include <vtkPiecewiseFunction.h>
#include <vtkGPUVolumeRayCastMapper.h>
#include <vtkFixedPointVolumeRayCastMapper.h>
#include <vtkVolumeProperty.h>
#include <vtkVolumeProperty.h>
#include <vtkImagePlaneWidget.h>
#include <vtkImageBlend.h>
#include <vtkCleanPolyData.h>
#include <vtkCaptionActor2D.h>
#include <itkGDCMImageIO.h>
#include <itkImage.h>
#include <vtkCutter.h>
#include <vtkImageReslice.h>
#include <vtkMatrix4x4.h>
#include <vtkTextActor.h>
#include <vtkTextWidget.h>
#include <qelapsedtimer.h>
#include <qmessagebox.h>
#include <qtablewidget.h>
#include <itkImageFileReader.h>
#include <itkImageToVTKImageFilter.h>
#include <itkImageSeriesReader.h>
#include <itkGDCMSeriesFileNames.h>
#include <itkImage.h>
#include <vtkSTLWriter.h>
#include <vtkOBJExporter.h>
#include "pointStore.h"
#include "pointPickerRealize.h"
#include "pointStoreRealize.h"
#include "optimizedPathGenerate.h"
#include "PointPickerInteractorStyle.h"
#include "myImageViewer2D.h"
#include <QSplitter.h>
#include <vtkTriangleFilter.h>

void ProjectMainWindow::onOpenSlot()
{
	this->horizontalSlider_1->setEnabled(0);
	this->horizontalSlider_2->setEnabled(0);
	this->horizontalSlider_3->setEnabled(0);
	this->opacity_slider->setEnabled(false);
	this->path1_widget->setEnabled(0);
	this->path3_widget->setEnabled(0);

	/*this->in_button->setEnabled(0);
	this->out_button->setEnabled(0);
	this->left_button->setEnabled(0);
	this->right_button->setEnabled(0);
	this->up_button->setEnabled(0);
	this->down_button->setEnabled(0);*/

	//this->u_d_scrollbar->setEnabled(0);
	this->u_d_scrollbar->setRange(-180, 180);
	this->u_d_scrollbar->setValue(0);
	//this->l_r_scrollbar->setEnabled(0);
	this->l_r_scrollbar->setRange(-180, 180);
	this->l_r_scrollbar->setValue(0);
	//this->spin_scrollbar->setEnabled(0);
	this->spin_scrollbar->setRange(-180, 180);
	this->spin_scrollbar->setValue(0);

	this->u_d_box->setValue(0);
	this->u_d_box->setRange(-180, 180);
	//this->u_d_box->setEnabled(0);
	this->l_r_box->setValue(0);
	this->l_r_box->setRange(-180, 180);
	//this->l_r_box->setEnabled(0);
	this->spin_box->setValue(0);
	this->spin_box->setRange(-180, 180);
	//this->spin_box->setEnabled(0);


	int resolution[3] = { 150, 30, 30 };//{ 100,6,1 };// 
	double angleOfDegree = 15;//23.02;


	QString filter;
	filter = "DICOM image file";

	QDir dir;
	QString fileName = QFileDialog::getExistingDirectory();//getOpenFileName(this, QString(tr("打开图像")), dir.absolutePath(), filter);

	if (fileName.isEmpty())
	{
		//this->output_pte->appendPlainText("--file path is illegal! ");、
		progressMiddle();
		progressEnd();
		this->rebuild_button->setEnabled(0);
		this->m_style->callback1->img_ornot = 0;
		this->m_style->callback2->img_ornot = 0;
		this->m_style->callback3->img_ornot = 0;
		this->m_style->callback1->contour_renderer->RemoveAllViewProps();
		this->m_style->callback2->contour_renderer->RemoveAllViewProps();
		this->m_style->callback3->contour_renderer->RemoveAllViewProps();
		this->operate_window->update();
		QString readingFile_fail = "---can not find dicom folder";
		readingFile_fail.append(fileName);
		this->output_pte->appendPlainText(readingFile_fail);
		return;
	}
	m_pRenderer->RemoveAllViewProps();
	m_pRenderer1->RemoveAllViewProps();
	m_pRenderer2->RemoveAllViewProps();
	m_pRenderer3->RemoveAllViewProps();
	// 支持带中文路径的读取
	QByteArray ba = fileName.toLocal8Bit();
	const char* fileName_str = ba.data();

	progressBegin();

	// 用vtkDICOMImageReader读取dicom数据
	/*vtkSmartPointer<vtkDICOMImageReader> dcm_reader = vtkSmartPointer<vtkDICOMImageReader>::New();
	float* patient_origin = dcm_reader->GetImagePositionPatient();
	m_style->patient_origin = patient_origin;
	dcm_reader->SetDirectoryName(fileName_str);
	this->m_style->bone_img_reader = dcm_reader;*/




	using PixelType = signed short;
	constexpr unsigned int Dimension = 3;

	QApplication::processEvents();
	//初始化待读取序列的格式类型
	using ImageType = itk::Image<PixelType, Dimension>;
	using ReaderType = itk::ImageSeriesReader<ImageType>;
	using ImageIOType = itk::GDCMImageIO;
	using NamesGeneratorType = itk::GDCMSeriesFileNames;

	QApplication::processEvents();
	//设置IO，并获取文件名
	ImageIOType::Pointer        gdcmIO = ImageIOType::New();
	NamesGeneratorType::Pointer namesGenerator = NamesGeneratorType::New();
	namesGenerator->SetInputDirectory(fileName_str);
	const ReaderType::FileNamesContainer& filenames =
		namesGenerator->GetInputFileNames();

	//输出文件名
	QApplication::processEvents();
	std::size_t numberOfFileNames = filenames.size();
	//读取dcm序列
	ReaderType::Pointer reader = ReaderType::New();
	reader->SetImageIO(gdcmIO);
	reader->SetFileNames(filenames);
	try
	{
		reader->Update();
	}
	catch (itk::ExceptionObject& e)
	{
		this->rebuild_button->setEnabled(0);
		this->m_style->callback1->img_ornot = 0;
		this->m_style->callback2->img_ornot = 0;
		this->m_style->callback3->img_ornot = 0;
		this->m_style->callback1->contour_renderer->RemoveAllViewProps();
		this->m_style->callback2->contour_renderer->RemoveAllViewProps();
		this->m_style->callback3->contour_renderer->RemoveAllViewProps();
		this->operate_window->update();
		QString readingFile_fail = "---can not find dicom files  in";
		readingFile_fail.append(fileName);
		progressMiddle();
		progressEnd();
		QString msg;
		msg.fromStdString(e.GetDescription());
		QMessageBox::critical(0, tr("Error"), msg + '\n' + tr("please select the right dir"));
		return;
	}

	QApplication::processEvents();

	itk::SmartPointer<itk::ImageToVTKImageFilter<itk::Image<signed short, 3>>> dcm_reader = itk::ImageToVTKImageFilter<itk::Image<signed short, 3>>::New();
	dcm_reader->SetInput(reader->GetOutput());
	dcm_reader->Update();
	this->m_style->bone_img_reader = dcm_reader;

	QApplication::processEvents();

	QString readingFile = "---reading file ";
	readingFile.append(fileName);
	readingFile.append("......");
	this->output_pte->appendPlainText(readingFile);

	std::string screw_path = "./resources/prothesis - 模型.stp-1 8.stp-1.STL";// "E:/research/ai shhoulder joint/shoulder joint/Qt/Qt-bin/Debug/resources/prothesis - 模型.stp-1 8.stp-1.STL";//
	vtkSmartPointer<vtkSTLReader> screw_reader =
		vtkSmartPointer<vtkSTLReader>::New();
	screw_reader->SetFileName(screw_path.c_str());
	screw_reader->Update();

	QApplication::processEvents();

	std::string base_path = "./resources/newBase.STL";//"E:/research/ai shhoulder joint/shoulder joint/Qt/Qt-bin/Debug/resources/newBase.STL";//
	vtkSmartPointer<vtkSTLReader> base_reader =
		vtkSmartPointer<vtkSTLReader>::New();
	base_reader->SetFileName(base_path.c_str());
	base_reader->Update();

	QApplication::processEvents();

	vtkSmartPointer<vtkImageCast> dcm_data =
		vtkSmartPointer<vtkImageCast>::New();
	dcm_data->SetInputData(dcm_reader->GetOutput());
	dcm_data->SetOutputScalarTypeToInt();
	dcm_data->Update();
	double range[2] = { dcm_data->GetOutput()->GetScalarRange()[0],dcm_data->GetOutput()->GetScalarRange()[1] };

	//if (range[1] == 1)
	//{
	//	//this->output_pte->appendPlainText("--file path is illegal! ");、
	//	progressMiddle();
	//	progressEnd();
	//	this->rebuild_button->setEnabled(0);
	//	this->m_style->callback1->img_ornot = 0;
	//	this->m_style->callback2->img_ornot = 0;
	//	this->m_style->callback3->img_ornot = 0;
	//	this->m_style->callback1->contour_renderer->RemoveAllViewProps();
	//	this->m_style->callback2->contour_renderer->RemoveAllViewProps();
	//	this->m_style->callback3->contour_renderer->RemoveAllViewProps();
	//	this->operate_window->update();
	//	QString readingFile_fail = "---can not find";
	//	readingFile_fail.append(fileName);
	//	this->output_pte->appendPlainText(readingFile_fail);
	//	return;
	//}

	/*QString patient_name ="\n--patient name";
	patient_name.append(dcm_reader->GetPatientName());
	patient_name.append('\n');
	this->output_pte->appendPlainText(patient_name);*/

	QApplication::processEvents();

	QString scl_range = "--schalar range of the DICOM: ";
	scl_range.append(QString::number(range[0]));
	scl_range.append(" ");
	scl_range.append(QString::number(range[1]));
	this->output_pte->appendPlainText(scl_range);

	vtkSmartPointer<vtkLookupTable> lut =
		vtkSmartPointer<vtkLookupTable>::New();
	lut->SetHueRange(0.0, 0.6);
	lut->SetAlphaRange(1.0, 1.0);
	lut->SetValueRange(1.0, 1.0);
	lut->SetSaturationRange(1.0, 1.0);
	lut->SetNumberOfTableValues(256);
	lut->SetRange(range);
	lut->Build();


	vtkSmartPointer<vtkMarchingCubes> boneExtractor = vtkSmartPointer<vtkMarchingCubes>::New();
	//vtkSmartPointer<vtkMarchingCubes> boneExtractor = vtkSmartPointer<vtkMarchingCubes>::New();

	boneExtractor->SetInputData(dcm_reader->GetOutput());
	boneExtractor->SetValue(0, this->marchingCubes_sb->value());
	boneExtractor->ComputeNormalsOn();


	QApplication::processEvents();

	//boneExtractor->GenerateValues(10, this->matchingCubes_sb->value(), this->matchingCubes_sb->value() + 500);  //设置提取的等值信息1
	vtkSmartPointer<vtkPoints> extract_point =
		vtkSmartPointer<vtkPoints>::New();
	extract_point->DeepCopy(boneExtractor->GetOutput()->GetPoints());

	progressMiddle();

	//剔除旧的或废除的数据单元，提高绘制速度
	vtkSmartPointer<vtkStripper> boneStripper = vtkSmartPointer<vtkStripper>::New(); //三角带连接           
	boneStripper->SetInputConnection(boneExtractor->GetOutputPort());

	/*QString cell = "cell:";
	cell.append(QString::number(boneExtractor->GetOutput()->GetNumberOfCells()));
	this->output_pte->appendPlainText(cell);*/

	//建立映射
	vtkSmartPointer <vtkPolyDataMapper> boneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	boneMapper->SetInputConnection(boneStripper->GetOutputPort());
	boneMapper->SetLookupTable(lut);
	boneMapper->SetScalarRange(range);
	boneMapper->SetScalarVisibility(1);

	QApplication::processEvents();

	//建立角色
	vtkSmartPointer<vtkActor> bone = vtkSmartPointer<vtkActor>::New();
	bone->SetMapper(boneMapper);
	boneMapper->ScalarVisibilityOff();
	bone->GetProperty()->SetDiffuseColor(1, 0.9, 0.8);
	//bone->GetProperty()->SetDiffuse(0.3);
	//bone->GetProperty()->SetSpecular(0.8);
	//bone->GetProperty()->SetSpecularPower(20);
	bone->GetProperty()->SetOpacity(1);
	//bone->GetProperty()->SetColor(0.5, 0.5, 0.5);
	bone->GetProperty()->ShadingOn();



	//vtkSmartPointer<vtkGPUVolumeRayCastMapper> volumeMapper =
	//	vtkSmartPointer<vtkGPUVolumeRayCastMapper>::New();
	//volumeMapper->SetInputData(dcm_reader->GetOutput());;
	//volumeMapper->SetSampleDistance(volumeMapper->GetSampleDistance() / 2);	//设置光线采样距离
	////volumeMapper->SetAutoAdjustSampleDistances(0);//设置图像采样步长
	////volumeMapper->SetImageSampleDistance(4);
	///*************************************************************************/
	//vtkSmartPointer<vtkVolumeProperty> volumeProperty =
	//	vtkSmartPointer<vtkVolumeProperty>::New();
	//volumeProperty->SetInterpolationTypeToLinear();
	//volumeProperty->ShadeOn();  //打开或者关闭阴影测试
	//volumeProperty->SetAmbient(0.4);
	//volumeProperty->SetDiffuse(0.6);  //漫反射
	//volumeProperty->SetSpecular(0.2); //镜面反射
	////设置不透明度
	//vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =
	//	vtkSmartPointer<vtkPiecewiseFunction>::New();
	//compositeOpacity->AddPoint(70, 0.00);
	//compositeOpacity->AddPoint(90, 0.40);
	//compositeOpacity->AddPoint(180, 0.60);
	//volumeProperty->SetScalarOpacity(compositeOpacity); //设置不透明度传输函数
	////设置梯度不透明属性
	//vtkSmartPointer<vtkPiecewiseFunction> volumeGradientOpacity =
	//	vtkSmartPointer<vtkPiecewiseFunction>::New();
	//volumeGradientOpacity->AddPoint(10, 0.0);
	//volumeGradientOpacity->AddPoint(90, 0.5);
	//volumeGradientOpacity->AddPoint(100, 1.0);
	//volumeProperty->SetGradientOpacity(volumeGradientOpacity);//设置梯度不透明度效果对比
	////设置颜色属性
	//vtkSmartPointer<vtkColorTransferFunction> color =
	//	vtkSmartPointer<vtkColorTransferFunction>::New();
	//color->AddRGBPoint(0.000, 0.00, 0.00, 0.00);
	//color->AddRGBPoint(64.00, 1.00, 0.52, 0.30);
	//color->AddRGBPoint(190.0, 1.00, 1.00, 1.00);
	//color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);
	//volumeProperty->SetColor(color);
	///********************************************************************************/
	//vtkSmartPointer<vtkVolume> volume =
	//	vtkSmartPointer<vtkVolume>::New();
	//volume->SetMapper(volumeMapper);
	//volume->SetProperty(volumeProperty);

	//this->m_pRenderer->AddVolume(volume);








	vtkSmartPointer<vtkCellPicker> Picker =
		vtkSmartPointer<vtkCellPicker>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();//vtkRenderWindowInteractor::SafeDownCast(obj);
	renderWindowInteractor->SetPicker(Picker);
	renderWindowInteractor->SetRenderWindow(operate_window->GetRenderWindow());


	double bone_center[3] = { dcm_reader->GetOutput()->GetCenter()[0],dcm_reader->GetOutput()->GetCenter()[1], dcm_reader->GetOutput()->GetCenter()[2] };

	this->m_style->initialize(boneStripper->GetOutput(), bone, dcm_reader->GetOutput(), dcm_data, screw_reader->GetOutput(), base_reader->GetOutput(), resolution, angleOfDegree, range, bone_center, extract_point, boneExtractor);
	this->m_style->text_out = this->output_pte;
	this->threshold1_sb->setValue(this->m_style->CTValueNormalize(this->marchingCubes_sb->value()) - this->m_style->threshold_offset);
	this->threshold2_sb->setValue(this->m_style->CTValueNormalize(this->marchingCubes_sb->value()) - this->m_style->threshold_offset);
	renderWindowInteractor->SetInteractorStyle(this->m_style);

	this->undo_button->setEnabled(1);
	this->opacity_slider->setEnabled(true);
	this->opacity_slider->setMaximum(100);
	this->opacity_slider->setMinimum(0);
	this->opacity_slider->setValue(100);
	//this->opacity_slider->setTickPosition(QSlider::TicksBothSides);
	this->horizontalSlider_1->setEnabled(1);
	this->horizontalSlider_2->setEnabled(1);
	this->horizontalSlider_3->setEnabled(1);
	this->horizontalSlider_1->setValue(0);
	this->horizontalSlider_2->setValue(0);
	this->horizontalSlider_3->setValue(0);
	this->rebuild_button->setEnabled(1);


	//创建一个camera
	vtkSmartPointer<vtkCamera> aCamera = vtkSmartPointer< vtkCamera>::New();
	aCamera->SetViewUp(0, 0, -1);
	aCamera->SetPosition(0, 1, 0);
	aCamera->SetFocalPoint(0, 0, 0);



	this->m_pRenderer->AddActor(bone);

	this->operate_window->update();
	//m_pRenderer->AddVolume(volume);
	//m_pRenderer->AddActor2D(scalarBar);



	vtkSmartPointer<vtkAxesActor> axesActor =
		vtkSmartPointer<vtkAxesActor>::New();
	this->axesWidget->SetOrientationMarker(axesActor);

	vtkSmartPointer<vtkNamedColors> colours =
		vtkSmartPointer<vtkNamedColors>::New();
	double r = 0;
	double g = 0;
	double b = 0;
	colours->GetColor("Wheat", r, g, b);
	this->axesWidget->SetInteractor(renderWindowInteractor);
	this->axesWidget->SetViewport(0.0, 0.0, 0.2, 0.3);
	this->axesWidget->SetOutlineColor(r, g, b);
	this->axesWidget->SetEnabled(1);
	this->axesWidget->InteractiveOn();

	//vtkSmartPointer<vtkTextActor> textActor =
	//	vtkSmartPointer<vtkTextActor>::New();
	//textActor->SetTextScaleModeToProp();
	////textActor->SetDisplayPosition(90, 50);//Position
	//textActor->SetInput(fileName_str);
	//textActor->GetActualPosition2Coordinate()->SetCoordinateSystemToNormalizedViewport();
	//textActor->GetPosition2Coordinate()->SetValue(0.1, 0.9);


	//textActor->GetTextProperty()->SetFontSize(12);
	//textActor->GetTextProperty()->SetFontFamilyToArial();
	//textActor->GetTextProperty()->SetJustificationToCentered();
	//textActor->GetTextProperty()->BoldOn();
	//textActor->GetTextProperty()->ItalicOn();
	//textActor->GetTextProperty()->ShadowOn();
	//textActor->GetTextProperty()->SetColor(1, 1, 1);
	//this->textWidget->SetTextActor(textActor);
	//this->textWidget->SetCurrentRenderer(this->m_pRenderer);
	//this->textWidget->SetInteractor(renderWindowInteractor);





	this->m_pRenderer->SetActiveCamera(aCamera);
	//bone_renderer->ResetCamera();
	aCamera->Dolly(1.5);
	//m_pRenderer->SetBackground(1, 1, 1);
	this->m_pRenderer->ResetCameraClippingRange();
	this->m_pRenderer->ResetCamera();
	this->m_pRenderer->GetActiveCamera()->Zoom(1.5);;
	this->m_pRenderer->DrawOn();
	this->operate_window->GetRenderWindow()->Render();



	this->path_button->setEnabled(true);
	this->clip_first_on->setEnabled(true);


	QApplication::processEvents();
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int extent[6];
	double spacing[3];
	double origin[3];
	dcm_reader->GetOutput()->GetExtent(extent);
	/*this->output_pte->appendPlainText(QString::number(extent[0]));
	this->output_pte->appendPlainText(QString::number(extent[1]));
	this->output_pte->appendPlainText(QString::number(extent[2]));
	this->output_pte->appendPlainText(QString::number(extent[3]));
	this->output_pte->appendPlainText(QString::number(extent[4]));
	this->output_pte->appendPlainText(QString::number(extent[5]));*/
	dcm_reader->GetOutput()->GetSpacing(spacing);
	dcm_reader->GetOutput()->GetOrigin(origin);

	int half[3] = { (extent[0] + extent[1]) ,(extent[2] + extent[3]) , (extent[4] + extent[5]) };

	double center[3];
	center[0] = origin[0] + spacing[0] * 0.5 * half[0];
	center[1] = origin[1] + spacing[1] * 0.5 * half[1];
	center[2] = origin[2] + spacing[2] * 0.5 * half[2];

	static double sagittalElements[16] = {
		0, 0,-1, 0,
		1, 0, 0, 0,
		0,-1, 0, 0,
		0, 0, 0, 1 };

	static double cornalElements[16] = {
		1, 0, 0, 0,
		0, 0, 1, 0,
		0, -1,0, 0,
		0, 0, 0, 1 };


	static double obliqueElements[16] = {
		1, 0, 0, 0,
		0, 0.866025, -0.5, 0,
		0, 0.5, 0.866025, 0,
		0, 0, 0, 1 };


	static double axialElements[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	double x[3] = { 1, 0, 0 };
	double y[3] = { 0, 1, 0 };
	double z[3] = { 0, 0, 1 };

	vtkSmartPointer<vtkMatrix4x4> resliceAxes1 =
		vtkSmartPointer<vtkMatrix4x4>::New();
	resliceAxes1->DeepCopy(axialElements);


	resliceAxes1->SetElement(0, 3, center[0]);
	resliceAxes1->SetElement(1, 3, center[1]);
	resliceAxes1->SetElement(2, 3, center[2]);

	vtkSmartPointer<vtkMatrix4x4> resliceAxes2 =
		vtkSmartPointer<vtkMatrix4x4>::New();
	resliceAxes2->DeepCopy(sagittalElements);

	resliceAxes2->SetElement(0, 3, center[0]);
	resliceAxes2->SetElement(1, 3, center[1]);
	resliceAxes2->SetElement(2, 3, center[2]);

	vtkSmartPointer<vtkMatrix4x4> resliceAxes3 =
		vtkSmartPointer<vtkMatrix4x4>::New();
	resliceAxes3->DeepCopy(cornalElements);

	resliceAxes3->SetElement(0, 3, center[0]);
	resliceAxes3->SetElement(1, 3, center[1]);
	resliceAxes3->SetElement(2, 3, center[2]);

	vtkSmartPointer<vtkImageReslice> reslice1 =
		vtkSmartPointer<vtkImageReslice>::New();
	reslice1->SetInputData(dcm_reader->GetOutput());
	reslice1->SetOutputDimensionality(2);
	//#if 0
	reslice1->SetResliceAxes(resliceAxes1);
	//#else
		//reslice1->SetResliceAxesDirectionCosines(x, y, z);
		//reslice1->SetResliceAxesOrigin(center);
	//#endif
	reslice1->SetInterpolationModeToLinear();



	vtkSmartPointer<vtkImageReslice> reslice2 =
		vtkSmartPointer<vtkImageReslice>::New();
	reslice2->SetInputData(dcm_reader->GetOutput());
	reslice2->SetOutputDimensionality(2);
	//#if 0
	reslice2->SetResliceAxes(resliceAxes2);
	//#else
	//	reslice2->SetResliceAxesDirectionCosines(x, y, z);
	//	reslice2->SetResliceAxesOrigin(center);
	//#endif
	reslice2->SetInterpolationModeToLinear();

	vtkSmartPointer<vtkImageReslice> reslice3 =
		vtkSmartPointer<vtkImageReslice>::New();
	reslice3->SetInputData(dcm_reader->GetOutput());
	reslice3->SetOutputDimensionality(2);
	//#if 0
	reslice3->SetResliceAxes(resliceAxes3);
	//#else
	//	reslice3->SetResliceAxesDirectionCosines(x, y, z);
	//	reslice3->SetResliceAxesOrigin(center);
	//#endif
	reslice3->SetInterpolationModeToLinear();





	vtkSmartPointer<vtkImageMapToColors> colorMap1 =
		vtkSmartPointer<vtkImageMapToColors>::New();
	colorMap1->SetLookupTable(this->m_style->colorTable);
	colorMap1->SetInputConnection(reslice1->GetOutputPort());
	colorMap1->Update();

	vtkSmartPointer<vtkImageMapToColors> colorMap2 =
		vtkSmartPointer<vtkImageMapToColors>::New();
	colorMap2->SetLookupTable(this->m_style->colorTable);
	colorMap2->SetInputConnection(reslice2->GetOutputPort());
	colorMap2->Update();

	vtkSmartPointer<vtkImageMapToColors> colorMap3 =
		vtkSmartPointer<vtkImageMapToColors>::New();
	colorMap3->SetLookupTable(this->m_style->colorTable);
	colorMap3->SetInputConnection(reslice3->GetOutputPort());
	colorMap3->Update();

	vtkSmartPointer<vtkImageActor> imgActor1 =
		vtkSmartPointer<vtkImageActor>::New();
	imgActor1->GetMapper()->SetInputConnection(colorMap1->GetOutputPort());
	//imgActor->SetInputData(colorMap->GetOutput());
	this->m_pRenderer1->AddActor(imgActor1);
	this->m_pRenderer1->SetBackground(0, 0, 0);

	vtkSmartPointer<vtkImageActor> imgActor2 =
		vtkSmartPointer<vtkImageActor>::New();
	imgActor2->GetMapper()->SetInputConnection(colorMap2->GetOutputPort());
	//imgActor->SetInputData(colorMap->GetOutput());
	this->m_pRenderer2->AddActor(imgActor2);
	this->m_pRenderer2->SetBackground(0, 0, 0);

	vtkSmartPointer<vtkImageActor> imgActor3 =
		vtkSmartPointer<vtkImageActor>::New();
	imgActor3->GetMapper()->SetInputConnection(colorMap3->GetOutputPort());
	//imgActor->SetInputData(colorMap->GetOutput());
	this->m_pRenderer3->AddActor(imgActor3);
	this->m_pRenderer3->SetBackground(0, 0, 0);


	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor1 =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> imagestyle1 =
		vtkSmartPointer<vtkInteractorStyleImage>::New();;
	renderWindowInteractor1->SetInteractorStyle(imagestyle1);
	renderWindowInteractor1->SetRenderWindow(this->qvtkWidget_1->GetRenderWindow());


	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor2 =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> imagestyle2 =
		vtkSmartPointer<vtkInteractorStyleImage>::New();
	renderWindowInteractor2->SetInteractorStyle(imagestyle2);
	renderWindowInteractor2->SetRenderWindow(this->qvtkWidget_2->GetRenderWindow());


	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor3 =
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	vtkSmartPointer<vtkInteractorStyleImage> imagestyle3 =
		vtkSmartPointer<vtkInteractorStyleImage>::New();
	renderWindowInteractor3->SetInteractorStyle(imagestyle3);
	renderWindowInteractor3->SetRenderWindow(this->qvtkWidget_3->GetRenderWindow());



	this->m_style->callback1->SetImageReslice(reslice1);
	this->m_style->callback1->SetInteractor(renderWindowInteractor1);
	this->m_style->callback1->SetMapToColors(colorMap1);
	this->m_style->callback1->setImageData(this->m_style->bone_img_reader->GetOutput(), this->m_style->bone_center,this->m_pRenderer1,this->m_style);
	//callback1->setFlag(0);
	this->m_style->callback1->SetRenderWindow(qvtkWidget_1->GetRenderWindow());
	imagestyle1->AddObserver(vtkCommand::MouseMoveEvent, this->m_style->callback1);
	imagestyle1->AddObserver(vtkCommand::LeftButtonPressEvent, this->m_style->callback1);
	imagestyle1->AddObserver(vtkCommand::LeftButtonReleaseEvent, this->m_style->callback1);
	//imagestyle1->AddObserver(vtkCommand::MiddleButtonPressEvent, this->m_style->callback1);
	//imagestyle1->AddObserver(vtkCommand::MiddleButtonReleaseEvent, this->m_style->callback1);
	//this->horizontalSlider_1->setEnabled(1);



	this->m_style->callback2->SetImageReslice(reslice2);
	this->m_style->callback2->SetInteractor(renderWindowInteractor2);
	this->m_style->callback2->SetMapToColors(colorMap2);
	this->m_style->callback2->setImageData(this->m_style->bone_img_reader->GetOutput(), this->m_style->bone_center,this->m_pRenderer2,this->m_style);
	//callback2->setFlag(0);
	this->m_style->callback2->SetRenderWindow(this->qvtkWidget_2->GetRenderWindow());
	imagestyle2->AddObserver(vtkCommand::MouseMoveEvent, this->m_style->callback2);
	imagestyle2->AddObserver(vtkCommand::LeftButtonPressEvent, this->m_style->callback2);
	imagestyle2->AddObserver(vtkCommand::LeftButtonReleaseEvent, this->m_style->callback2);
	//imagestyle2->AddObserver(vtkCommand::MiddleButtonPressEvent, this->m_style->callback2);
	//imagestyle2->AddObserver(vtkCommand::MiddleButtonReleaseEvent, this->m_style->callback2);
	//this->horizontalSlider_2->setEnabled(1);


	/*vtkSmartPointer<vtkImageInteractionCallback> callback3 =
		vtkSmartPointer<vtkImageInteractionCallback>::New();*/
	this->m_style->callback3->SetImageReslice(reslice3);
	this->m_style->callback3->SetInteractor(renderWindowInteractor3);
	this->m_style->callback3->SetMapToColors(colorMap3);
	this->m_style->callback3->setImageData(this->m_style->bone_img_reader->GetOutput(), this->m_style->bone_center,this->m_pRenderer3,this->m_style);
	//callback3->setFlag(0);
	this->m_style->callback3->SetRenderWindow(this->qvtkWidget_3->GetRenderWindow());
	imagestyle3->AddObserver(vtkCommand::MouseMoveEvent, this->m_style->callback3);
	imagestyle3->AddObserver(vtkCommand::LeftButtonPressEvent, this->m_style->callback3);
	imagestyle3->AddObserver(vtkCommand::LeftButtonReleaseEvent, this->m_style->callback3);
	//imagestyle3->AddObserver(vtkCommand::MiddleButtonPressEvent, this->m_style->callback3);
	//imagestyle3->AddObserver(vtkCommand::MiddleButtonReleaseEvent, this->m_style->callback3);
	//this->horizontalSlider_3->setEnabled(1);





	/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	progressEnd();
	this->operate_window->update();

	this->qvtkWidget_1->GetRenderWindow()->Render();
	this->m_pRenderer1->ResetCamera();
	this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
	this->qvtkWidget_1->update();

	this->qvtkWidget_2->GetRenderWindow()->Render();
	this->m_pRenderer2->ResetCamera();
	this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
	this->qvtkWidget_2->update();

	this->qvtkWidget_3->GetRenderWindow()->Render();
	this->m_pRenderer3->ResetCamera();
	this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
	this->qvtkWidget_3->update();
	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}
	return;
}

void ProjectMainWindow::updateCoords(vtkObject* obj)
{
	// 获取交互器
	vtkRenderWindowInteractor* iren = vtkRenderWindowInteractor::SafeDownCast(obj);

	// 获取鼠标的当前位置
	int event_pos[2];
	iren->GetEventPosition(event_pos);

	QString str;
	str.sprintf("x=%d : y=%d", event_pos[0], event_pos[1]);
	this->m_StatusBar->showMessage(str);

	/*if (this->clip_first_on->isChecked())
	{
		qDebug() << "clip checkbox is on!" << endl;
		m_style->planeOrNot = true;
		if (this->m_style->pointNum == 3)
		{
			this->clip_button->setEnabled(true);
		}
	}*/
}




void ProjectMainWindow::undoLastOperation()
{
	int num_of_point = this->m_style->pointNum;
	vtkSmartPointer<vtkActorCollection> actorCollection =
		vtkSmartPointer<vtkActorCollection>::New();

	if (num_of_point == 0)
	{
		if (this->m_style->clippedOrNot || this->m_style->segmentOrNot)
		{
			progressBegin();
			this->m_pRenderer->RemoveActor(this->m_pRenderer->GetActors()->GetLastActor());
			this->m_pRenderer->AddActor(this->m_style->bone_origin_actor);
			progressMiddle();
			this->m_style->clippedOrNot = false;
			this->m_style->segmentOrNot = false;
			this->m_style->bone_cur_actor = this->m_pRenderer->GetActors()->GetLastActor();

			this->operate_window->update();
		}
	}

	else if (num_of_point == 3)
	{
		progressBegin();
		if (this->clip_first_on->isChecked())
		{
			this->m_style->point->deleteLastPoint();
			this->m_style->pointNum--;
			actorCollection = m_pRenderer->GetActors();
			this->m_pRenderer->RemoveActor(actorCollection->GetLastActor());

		}
		else
		{
			this->m_style->point->deleteLastPoint();
			this->m_style->pointNum--;
			this->m_style->point->deleteLastPoint();
			this->m_style->pointNum--;
			this->m_pRenderer->RemoveActor(this->m_style->plane_actor);
			this->m_style->planeOrNot = false;
		}
		progressMiddle();

		this->operate_window->update();
	}

	else if (this->m_pRenderer->GetActors()->GetNumberOfItems() >= 5 && this->m_style->finish == false)
	{
		progressBegin();
		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_pRenderer->RemoveActor(this->m_style->base_actor);
		this->m_pRenderer->RemoveActor(this->m_style->actor_cone1);
		this->m_pRenderer->RemoveActor(this->m_style->actor_cone2);
		this->m_pRenderer->AddActor(this->m_style->plane_actor);
		progressMiddle();
		progressEnd();
		this->operate_window->update();

		this->u_d_scrollbar->setValue(0);
		this->l_r_scrollbar->setValue(0);
		this->spin_scrollbar->setValue(0);

		this->u_d_box->setValue(0);
		this->l_r_box->setValue(0);
		this->spin_box->setValue(0);

	}

	else if (this->m_pRenderer->GetActors()->GetNumberOfItems() >= 5 && this->m_style->finish)
	{
		progressBegin();
		this->m_style->finish = false;
		/*this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;*/

		actorCollection = m_pRenderer->GetActors();
		this->m_pRenderer->RemoveActor(actorCollection->GetLastActor());
		actorCollection = m_pRenderer->GetActors();
		this->m_pRenderer->RemoveActor(actorCollection->GetLastActor());
		actorCollection = m_pRenderer->GetActors();
		this->m_pRenderer->RemoveActor(actorCollection->GetLastActor());
		/*actorCollection = m_pRenderer->GetActors();
		this->m_pRenderer->RemoveActor(actorCollection->GetLastActor());
		actorCollection = m_pRenderer->GetActors();
		this->m_pRenderer->RemoveActor(actorCollection->GetLastActor());*/
		progressMiddle();

		this->m_pRenderer->AddActor(this->m_style->actor_cone1);
		this->m_pRenderer->AddActor(this->m_style->actor_cone2);
		this->m_pRenderer->AddActor(this->m_style->base_actor);

		//去除可能残余的轮廓线;
		//this->m_pRenderer1->ResetCamera();
		//this->m_pRenderer1->GetActiveCamera()->Zoom(1.2);
		//m_pRenderer->GetActiveCamera()->SetWindowCenter(-1, -0.8);
		this->m_style->callback1->prosthesisOrNot = 0;
		this->m_style->callback1->contour_renderer->RemoveAllViewProps();
		this->m_style->callback1->contour_renderer->AddActor(this->m_style->callback1->x_line_actor);
		this->m_style->callback1->contour_renderer->AddActor(this->m_style->callback1->y_line_actor);
		this->qvtkWidget_1->update();

		//this->m_pRenderer2->ResetCamera();
		//this->m_pRenderer2->GetActiveCamera()->Zoom(1.2);
		//m_pRenderer2->GetActiveCamera()->SetWindowCenter(-1, -0.8);
		this->m_style->callback2->prosthesisOrNot = 0;
		this->m_style->callback2->contour_renderer->RemoveAllViewProps();
		this->m_style->callback2->contour_renderer->AddActor(this->m_style->callback2->x_line_actor);
		this->m_style->callback2->contour_renderer->AddActor(this->m_style->callback2->y_line_actor);
		this->qvtkWidget_2->update();

		//this->m_pRenderer3->ResetCamera();
		//this->m_pRenderer3->GetActiveCamera()->Zoom(1.2);
		//m_pRenderer3->GetActiveCamera()->SetWindowCenter(-1, -0.8);
		this->m_style->callback3->prosthesisOrNot = 0;
		this->m_style->callback3->contour_renderer->RemoveAllViewProps();
		this->m_style->callback3->contour_renderer->AddActor(this->m_style->callback3->x_line_actor);
		this->m_style->callback3->contour_renderer->AddActor(this->m_style->callback3->y_line_actor);
		this->qvtkWidget_3->update();

		this->path1_widget->setEnabled(0);
		this->path3_widget->setEnabled(0);

		this->operate_window->update();
	}

	else
	{
		progressBegin();
		this->m_style->point->deleteLastPoint();
		//qDebug() << "point number:" << m_style->pointNum << endl;
		this->m_style->pointNum--;
		progressMiddle();
		actorCollection = m_pRenderer->GetActors();
		this->m_pRenderer->RemoveActor(actorCollection->GetLastActor());

		this->operate_window->update();
	}

	QString numOfP = "--Number of points left: ";
	numOfP.append(QString::number(this->m_style->pointNum));
	this->output_pte->appendPlainText(numOfP);
	progressEnd();
	return;
}


void ProjectMainWindow::clipOrNot()
{

	if (this->clip_first_on->isChecked())
	{
		this->output_pte->appendPlainText("--clip checkbox is on!");
		this->m_style->planeOrNot = true;
		this->clip_button->setEnabled(true);
	}

	if (this->clip_first_on->isChecked() == false)
	{
		this->output_pte->appendPlainText("--clip checkbox is off!");
		this->m_style->planeOrNot = false;
		this->clip_button->setEnabled(false);
	}
}


void ProjectMainWindow::clip()
{

	this->clip_button->move(this->clip_button->geometry().x(), this->clip_button->geometry().y() + 10);
	QThread::msleep(200);
	this->clip_button->move(this->clip_button->geometry().x(), this->clip_button->geometry().y() - 10);

	if (this->m_style->pointNum == 3)
	{
		progressBegin();
		double point1[3] = { this->m_style->point->getPoint(1)[0], this->m_style->point->getPoint(1)[1],this->m_style->point->getPoint(1)[2] };
		double point2[3] = { this->m_style->point->getPoint(2)[0], this->m_style->point->getPoint(2)[1],this->m_style->point->getPoint(2)[2] };
		double point3[3] = { this->m_style->point->getPoint(3)[0], this->m_style->point->getPoint(3)[1],this->m_style->point->getPoint(3)[2] };

		double vec1[3] = { point2[0] - point1[0],point2[1] - point1[1], point2[2] - point1[2] };
		double vec2[3] = { point3[0] - point1[0],point3[1] - point1[1], point3[2] - point1[2] };

		double normal[3] = { vec1[1] * vec2[2] - vec1[2] * vec2[1],
							 vec1[2] * vec2[0] - vec1[0] * vec2[2],
							 vec1[0] * vec2[1] - vec1[1] * vec2[0] };

		vtkMath::Normalize(normal);

		vtkSmartPointer<vtkPlane> plane =
			vtkSmartPointer<vtkPlane>::New();
		plane->SetOrigin(point1);
		plane->SetNormal(normal);

		vtkSmartPointer<vtkClipPolyData> clip_data =
			vtkSmartPointer<vtkClipPolyData>::New();

		clip_data->SetInputData(this->m_style->bone_cur_actor->GetMapper()->GetInput());
		clip_data->SetClipFunction(plane);
		clip_data->GenerateClippedOutputOn();
		clip_data->Update();

		progressMiddle();

		this->m_pRenderer->RemoveAllViewProps();
		this->m_pRenderer->GetActors()->RemoveAllItems();



		/*	vtkSmartPointer<vtkAxesActor> axesActor =
				vtkSmartPointer<vtkAxesActor>::New();
			axesActor->AxisLabelsOn();
			axesActor->SetCylinderRadius(axesActor->GetCylinderRadius() * 2);
			axesActor->GetXAxisCaptionActor2D()->GetProperty()->SetColor(1, 0, 0);
			axesActor->GetYAxisCaptionActor2D()->GetProperty()->SetColor(0, 2, 0);
			axesActor->GetZAxisCaptionActor2D()->GetProperty()->SetColor(0, 0, 3);
			axesActor->SetConeRadius(axesActor->GetCylinderRadius());
			axesActor->SetTotalLength(70, 70, 70);
			m_pRenderer->AddActor(axesActor);*/


		vtkSmartPointer<vtkPolyDataMapper> clip_mapper1 =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		clip_mapper1->SetInputConnection(clip_data->GetOutputPort());
		clip_mapper1->ScalarVisibilityOff();
		//m_style->bonePolyData = clip_data->GetOutput();

		vtkSmartPointer<vtkPolyDataMapper> clip_mapper2 =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		clip_mapper2->SetInputConnection(clip_data->GetClippedOutputPort());
		clip_mapper2->ScalarVisibilityOff();


		vtkSmartPointer<vtkActor> clip_actor1 =
			vtkSmartPointer<vtkActor>::New();
		clip_actor1->SetMapper(clip_mapper1);
		this->m_style->bone_cur_actor = clip_actor1;
		vtkSmartPointer<vtkNamedColors> colors =
			vtkSmartPointer<vtkNamedColors>::New();
		/*clip_actor1->GetProperty()->SetDiffuseColor(colors->GetColor3d("Ivory").GetData());
		clip_actor1->GetProperty()->SetDiffuse(0.0);
		clip_actor1->GetProperty()->SetSpecular(0.3);
		clip_actor1->GetProperty()->ShadingOn();*/
		//bone->GetProperty()->SetSpecularPower(20);
		clip_actor1->GetProperty()->SetDiffuseColor(1, 0.9, 0.8);
		clip_actor1->GetProperty()->SetOpacity(1);



		vtkSmartPointer<vtkActor> clip_actor2 =
			vtkSmartPointer<vtkActor>::New();
		clip_actor2->SetMapper(clip_mapper2);
		clip_actor2->GetProperty()->SetOpacity(0);
		/*clip_actor2->GetProperty()->SetDiffuseColor(colors->GetColor3d("Ivory").GetData());
		clip_actor2->GetProperty()->SetDiffuse(0.0);
		clip_actor2->GetProperty()->SetSpecular(0.3);
		clip_actor2->GetProperty()->ShadingOn();*/
		//bone->GetProperty()->SetSpecularPower(20);
		clip_actor2->GetProperty()->SetOpacity(0);
		clip_actor2->GetProperty()->SetDiffuseColor(1, 0.9, 0.8);

		this->m_pRenderer->AddActor(clip_actor1);
		this->m_pRenderer->AddActor(clip_actor2);

		this->m_style->clip_actor1 = clip_actor1;
		this->m_style->clip_actor2 = clip_actor2;

		this->output_pte->appendPlainText("--clipping finish!");

		//m_style->boneActor->GetMapper()->AddClippingPlane(plane);




		this->clip_button->setEnabled(false);
		this->clip_first_on->setChecked(false);

		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_style->planeOrNot = false;
		this->m_style->clippedOrNot = true;


		/*m_pRenderder->RemoveAllViewProps();
		vtkSmartPointer<vtkMapper> clip_Mapper =
			vtkSmartPointer<vtkMapper>::New();*/
		this->change_button->setEnabled(true);
		progressEnd();
		this->operate_window->update();
	}
	else
	{
		this->output_pte->appendPlainText("--clip_button is unable!");
		return;
	}
	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}
}


void ProjectMainWindow::changeClippingArea()
{
	progressBegin();
	if (this->m_style->clip_actor1->GetProperty()->GetOpacity() == 1)
	{
		this->m_style->clip_actor1->GetProperty()->SetOpacity(0);
		this->m_style->clip_actor2->GetProperty()->SetOpacity(1);
		this->m_style->bone_cur_actor = this->m_style->clip_actor2;

	}
	else
	{
		this->m_style->clip_actor1->GetProperty()->SetOpacity(1);
		this->m_style->clip_actor2->GetProperty()->SetOpacity(0);
		this->m_style->bone_cur_actor = this->m_style->clip_actor1;
	}
	progressMiddle();
	progressEnd();
	this->operate_window->update();
}


void ProjectMainWindow::changeThreshold()
{
	this->m_style->threshold1 = this->threshold1_sb->value();
	this->m_style->threshold2 = this->threshold2_sb->value();
	QString str = "\n--threshold of path1:";
	str.append(QString::number(this->m_style->threshold1, 10));
	str.append("\n--threshold of path3:");
	str.append(QString::number(this->m_style->threshold2, 10));
	str.append("\n");
	this->output_pte->appendPlainText(str);
}


void ProjectMainWindow::on_plainTextEdit_customContextMenuRequested(const QPoint& pos)
{
	//创建并显示标准弹出式菜单
	QMenu* menu = this->output_pte->createStandardContextMenu();
	menu->exec(pos);
}


void ProjectMainWindow::path_display()
{
	this->undo_button->setEnabled(0);
	this->in_button->setEnabled(0);
	this->out_button->setEnabled(0);
	this->up_button->setEnabled(0);
	this->down_button->setEnabled(0);
	this->right_button->setEnabled(0);
	this->left_button->setEnabled(0);
	this->rebuild_button->setEnabled(0);
	this->seg_button->setEnabled(0);


	if (this->m_style->pointNum == 7 && this->m_style->finish == false)
	{
		this->output_pte->appendPlainText("\n\n\n--Processing......");
		progressBegin();
		this->m_style->finish = true;

		/*double middle_len = 14.72;
		double distance = 12.8;
		double screwLen = 38.8;*/
		this->m_pRenderer->RemoveActor(this->m_style->base_actor);


		double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
								  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
								  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
		vtkMath::Normalize(dir_vectors);

		//double point5[3] = { this->m_style->point->getPoint(1)[0] - dir_vectors[0] ,
		//					 this->m_style->point->getPoint(1)[1] - dir_vectors[1] ,
		//					 this->m_style->point->getPoint(1)[2] - dir_vectors[2] };
		//this->m_style->point->addPoint(point5);
		//this->m_style->pointNum++;


		////double* inplant_point = m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5));
		///*this->output_pte->appendPlainText("\n\n\n*************************************");
		//this->output_pte->appendPlainText(QString::number(inplant_point[8]));*/
		//double inplant_point[9] = { m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5))[0],
		//							m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5))[1],
		//							m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5))[2],
		//							m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5))[3],
		//							m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5))[4],
		//							m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5))[5],
		//							m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5))[6],
		//							m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5))[7],
		//							m_style->inPlantPoint(m_style->distance, m_style->point->getPoint(1), m_style->point->getPoint(4), m_style->point->getPoint(5))[8] };

		//this->m_style->finalPath[0] = inplant_point[0];
		//this->m_style->finalPath[1] = inplant_point[1];
		//this->m_style->finalPath[2] = inplant_point[2];
		//this->m_style->finalPath[6] = inplant_point[3];
		//this->m_style->finalPath[7] = inplant_point[4];
		//this->m_style->finalPath[8] = inplant_point[5];
		//this->m_style->finalPath[12] = inplant_point[6];
		//this->m_style->finalPath[13] = inplant_point[7];
		//this->m_style->finalPath[14] = inplant_point[8];

		//
		//double inplant_point1[3] = { inplant_point[0] - 3.40 * m_style->planeNormal[0],inplant_point[1] - 3.40 * m_style->planeNormal[1], inplant_point[2] - 3.40 * m_style->planeNormal[2] };
		//double inplant_point2[3] = { inplant_point[6] - 3.40 * m_style->planeNormal[0],inplant_point[7] - 3.40 * m_style->planeNormal[1], inplant_point[8] - 3.40 * m_style->planeNormal[2] };
		//m_style->point->addPoint(inplant_point1);
		//m_style->pointNum++;
		//m_style->pointVisualize(m_style->pointNum);

		//m_style->point->addPoint(inplant_point2);
		//m_style->pointNum++;
		//m_style->pointVisualize(m_style->pointNum);

		/*this->m_style->screw_apex1[0] = inplant_point1[0];
		this->m_style->screw_apex1[1] = inplant_point1[1];
		this->m_style->screw_apex1[2] = inplant_point1[2];
		this->m_style->screw_apex2[0] = inplant_point2[0];
		this->m_style->screw_apex2[1] = inplant_point2[1];
		this->m_style->screw_apex2[2] = inplant_point2[2];*/

		/*double vectors[3] = { inplant_point1[0] - inplant_point2[0],
							  inplant_point1[1] - inplant_point2[1],
							  inplant_point1[2] - inplant_point2[2] };

		vtkMath::Normalize(vectors);*/

		/*double offset[3] = { -m_style->planeNormal[1] * vectors[2] + m_style->planeNormal[2] * vectors[1],
							 -m_style->planeNormal[2] * vectors[0] + m_style->planeNormal[0] * vectors[2],
							 -m_style->planeNormal[0] * vectors[1] + m_style->planeNormal[1] * vectors[0] };*/

							 //vtkMath::Normalize(offset);
							 /*double cone_normal1[3] = { 0 };
							 double cone_normal2[3] = { 0 };

							 if (this->checkBox_r->isChecked())

							 {
								 cone_normal1[0] = m_style->planeNormal[0] + vectors[0] * tan(m_style->angleOfDegree * acos(-1) / 180) * 0.6 + 0.3 * offset[0];
								 cone_normal1[1] = m_style->planeNormal[1] + vectors[1] * tan(m_style->angleOfDegree * acos(-1) / 180) * 0.6 + 0.3 * offset[1];
								 cone_normal1[2] = m_style->planeNormal[2] + vectors[2] * tan(m_style->angleOfDegree * acos(-1) / 180) * 0.6 + 0.3 * offset[2];

								 cone_normal2[0] = m_style->planeNormal[0] - vectors[0] * tan(m_style->angleOfDegree * acos(-1) / 180) * 1.2 - 0.1 * offset[0];
								 cone_normal2[1] = m_style->planeNormal[1] - vectors[1] * tan(m_style->angleOfDegree * acos(-1) / 180) * 1.2 - 0.1 * offset[1];
								 cone_normal2[2] = m_style->planeNormal[2] - vectors[2] * tan(m_style->angleOfDegree * acos(-1) / 180) * 1.2 - 0.1 * offset[2];
							 }

							 if (this->checkBox_l->isChecked())

							 {
								 cone_normal1[0] = m_style->planeNormal[0] + vectors[0] * tan(m_style->angleOfDegree * acos(-1) / 180) * 0.6 - 0.3 * offset[0];
								 cone_normal1[1] = m_style->planeNormal[1] + vectors[1] * tan(m_style->angleOfDegree * acos(-1) / 180) * 0.6 - 0.3 * offset[1];
								 cone_normal1[2] = m_style->planeNormal[2] + vectors[2] * tan(m_style->angleOfDegree * acos(-1) / 180) * 0.6 - 0.3 * offset[2];

								 cone_normal2[0] = m_style->planeNormal[0] - vectors[0] * tan(m_style->angleOfDegree * acos(-1) / 180) * 1.2 + 0.1 * offset[0];
								 cone_normal2[1] = m_style->planeNormal[1] - vectors[1] * tan(m_style->angleOfDegree * acos(-1) / 180) * 1.2 + 0.1 * offset[1];
								 cone_normal2[2] = m_style->planeNormal[2] - vectors[2] * tan(m_style->angleOfDegree * acos(-1) / 180) * 1.2 + 0.1 * offset[2];
							 }*/

		vtkSmartPointer<vtkPoints> p1 = this->m_style->coneGenerate(this->m_style->point->getPoint(6), this->m_style->planeNormal, this->m_style->screwLen, this->m_style->resolution, this->m_style->angleOfDegree, dir_vectors);
		double* path1_points = this->m_style->generatePath(p1, this->m_style->boneIMGData, this->m_style->screwLen, this->m_style->resolution, this->m_style->threshold1);
		double path1_vectors[3] = { path1_points[3] - path1_points[0], path1_points[4] - path1_points[1], path1_points[5] - path1_points[2] };
		/*double path1_vectors[3] = { m_style->generatePath(p1, m_style->boneIMGData, screwLen, m_style->resolution)[3] - m_style->generatePath(p1, m_style->boneIMGData, screwLen, m_style->resolution)[0],
									m_style->generatePath(p1, m_style->boneIMGData, screwLen, m_style->resolution)[4] - m_style->generatePath(p1, m_style->boneIMGData, screwLen, m_style->resolution)[1],
									m_style->generatePath(p1, m_style->boneIMGData, screwLen, m_style->resolution)[5] - m_style->generatePath(p1, m_style->boneIMGData, screwLen, m_style->resolution)[2] };*/
		this->maxHu1 = path1_points[7];
		this->optimalHu1 = path1_points[6];
		QString av_path1 = "number of available path1:";
		av_path1.append(QString::number(this->m_style->avail_path));
		this->output_pte->appendPlainText(av_path1);
		this->m_pRenderer->RemoveActor(this->m_style->actor_cone1);
		vtkMath::Normalize(path1_vectors);
		this->m_style->finalPath[0] = this->m_style->point->getPoint(6)[0];
		this->m_style->finalPath[1] = this->m_style->point->getPoint(6)[1];
		this->m_style->finalPath[2] = this->m_style->point->getPoint(6)[2];
		this->m_style->finalPath[3] = this->m_style->finalPath[0] + path1_vectors[0] * this->m_style->screwLen;
		this->m_style->finalPath[4] = this->m_style->finalPath[1] + path1_vectors[1] * this->m_style->screwLen;
		this->m_style->finalPath[5] = this->m_style->finalPath[2] + path1_vectors[2] * this->m_style->screwLen;
		double screw_origin_apex[3] = { 10.1845, 7.67663, 14.14 };
		vtkSmartPointer<vtkTransform> screw_transform1 =
			vtkSmartPointer<vtkTransform>::New();
		screw_transform1->PostMultiply();
		screw_transform1->Translate(-screw_origin_apex[0], -screw_origin_apex[1], -screw_origin_apex[2]);

		double rollZ1 = acos(path1_vectors[0]) * 180 / acos(-1);
		double rollX1 = acos(abs(path1_vectors[1] / sqrt(1 - pow(path1_vectors[0], 2)))) * 180 / acos(-1);

		if (path1_vectors[0] > 0 && path1_vectors[1] > 0 && path1_vectors[2] > 0)
			rollX1 = rollX1;
		if (path1_vectors[0] > 0 && path1_vectors[1] > 0 && path1_vectors[2] < 0)
			rollX1 = -rollX1;
		if (path1_vectors[0] > 0 && path1_vectors[1] < 0 && path1_vectors[2] > 0)
			rollX1 = 180 - rollX1;
		if (path1_vectors[0] > 0 && path1_vectors[1] < 0 && path1_vectors[2] < 0)
			rollX1 = rollX1 - 180;
		if (path1_vectors[0] < 0 && path1_vectors[1] > 0 && path1_vectors[2] > 0)
			rollX1 = rollX1;
		if (path1_vectors[0] < 0 && path1_vectors[1] > 0 && path1_vectors[2] < 0)
			rollX1 = -rollX1;
		if (path1_vectors[0] < 0 && path1_vectors[1] < 0 && path1_vectors[2] > 0)
			rollX1 = 180 - rollX1;
		if (path1_vectors[0] < 0 && path1_vectors[1] < 0 && path1_vectors[2] < 0)
			rollX1 = rollX1 - 180;

		//std::cout << "roll:" << rollZ1 << ' ' << rollX1 << std::endl;
		screw_transform1->RotateZ(rollZ1);
		screw_transform1->RotateX(rollX1);//rollX1);
		//std::cout << inplant_point1[0] << " " << inplant_point1[1] << " " << inplant_point1[2] << std::endl;
		screw_transform1->Translate(this->m_style->point->getPoint(6));
		screw_transform1->Update();

		vtkSmartPointer<vtkTransformPolyDataFilter> screw1_transformPD =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();
		screw1_transformPD->SetTransform(screw_transform1);
		screw1_transformPD->SetInputData(this->m_style->screw_data);
		//screw1_transformPD->SetInputConnection(this->screw_data->)
		vtkSmartPointer<vtkPolyDataMapper> screw1_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		screw1_mapper->SetInputConnection(screw1_transformPD->GetOutputPort());
		//screw1_mapper->SetInputData(this->screw_data);

		vtkSmartPointer<vtkActor> screw1_actor =
			vtkSmartPointer<vtkActor>::New();
		screw1_actor->SetMapper(screw1_mapper);
		screw1_actor->GetProperty()->SetColor(0.8, 0.8, 0);
		screw1_actor->GetProperty()->SetOpacity(1);
		screw1_actor->SetVisibility(1);
		this->m_pRenderer->AddActor(screw1_actor);
		this->m_style->screw_actor1 = screw1_actor;
		this->operate_window->update();
		progressMiddle();

		double minus_dir_vectors[3] = { -dir_vectors[0],-dir_vectors[1],-dir_vectors[2] };
		double minus_planeNormal[3] = { -this->m_style->planeNormal[0],-this->m_style->planeNormal[1] , -this->m_style->planeNormal[2] };
		vtkSmartPointer<vtkPoints> p2 = this->m_style->coneGenerate(this->m_style->point->getPoint(7), this->m_style->planeNormal, this->m_style->screwLen, this->m_style->resolution, this->m_style->angleOfDegree, minus_dir_vectors);
		double* path2_points = this->m_style->generatePath(p2, this->m_style->boneIMGData, this->m_style->screwLen, this->m_style->resolution, this->m_style->threshold2);
		double path2_vectors[3] = { path2_points[3] - path2_points[0], path2_points[4] - path2_points[1], path2_points[5] - path2_points[2] };
		/*double path2_vectors[3] = { m_style->generatePath(p2, m_style->boneIMGData, screwLen, m_style->resolution)[3] - m_style->generatePath(p2, m_style->boneIMGData, screwLen, m_style->resolution)[0],
									m_style->generatePath(p2, m_style->boneIMGData, screwLen, m_style->resolution)[4] - m_style->generatePath(p2, m_style->boneIMGData, screwLen, m_style->resolution)[1],
									m_style->generatePath(p2, m_style->boneIMGData, screwLen, m_style->resolution)[5] - m_style->generatePath(p2, m_style->boneIMGData, screwLen, m_style->resolution)[2] };*/

		this->maxHu2 = path2_points[7];
		this->optimalHu2 = path2_points[6];
		QString av_path2 = "number of available path3:";
		av_path2.append(QString::number(this->m_style->avail_path));
		this->output_pte->appendPlainText(av_path2);
		vtkMath::Normalize(path2_vectors);
		this->m_style->finalPath[12] = this->m_style->point->getPoint(7)[0];
		this->m_style->finalPath[13] = this->m_style->point->getPoint(7)[1];
		this->m_style->finalPath[14] = this->m_style->point->getPoint(7)[2];
		this->m_style->finalPath[15] = this->m_style->finalPath[12] + path2_vectors[0] * this->m_style->screwLen;
		this->m_style->finalPath[16] = this->m_style->finalPath[13] + path2_vectors[1] * this->m_style->screwLen;
		this->m_style->finalPath[17] = this->m_style->finalPath[14] + path2_vectors[2] * this->m_style->screwLen;
		vtkSmartPointer<vtkTransform> screw_transform2 =
			vtkSmartPointer<vtkTransform>::New();
		screw_transform2->PostMultiply();
		screw_transform2->Translate(-screw_origin_apex[0], -screw_origin_apex[1], -screw_origin_apex[2]);

		double rollZ2 = acos(path2_vectors[0]) * 180 / acos(-1);
		double rollX2 = acos(abs(path2_vectors[1] / sqrt(1 - pow(path2_vectors[0], 2)))) * 180 / acos(-1);

		if (path2_vectors[0] > 0 && path2_vectors[1] > 0 && path2_vectors[2] > 0)
			rollX2 = rollX2;
		if (path2_vectors[0] > 0 && path2_vectors[1] > 0 && path2_vectors[2] < 0)
			rollX2 = -rollX2;
		if (path2_vectors[0] > 0 && path2_vectors[1] < 0 && path2_vectors[2] > 0)
			rollX2 = 180 - rollX2;
		if (path2_vectors[0] > 0 && path2_vectors[1] < 0 && path2_vectors[2] < 0)
			rollX2 = rollX2 - 180;
		if (path2_vectors[0] < 0 && path2_vectors[1] > 0 && path2_vectors[2] > 0)
			rollX2 = rollX2;
		if (path2_vectors[0] < 0 && path2_vectors[1] > 0 && path2_vectors[2] < 0)
			rollX2 = -rollX2;
		if (path2_vectors[0] < 0 && path2_vectors[1] < 0 && path2_vectors[2] > 0)
			rollX2 = 180 - rollX2;
		if (path2_vectors[0] < 0 && path2_vectors[1] < 0 && path2_vectors[2] < 0)
			rollX2 = rollX2 - 180;

		screw_transform2->RotateZ(rollZ2);
		screw_transform2->RotateX(rollX2);
		screw_transform2->Translate(this->m_style->point->getPoint(7));
		screw_transform2->Update();

		vtkSmartPointer<vtkTransformPolyDataFilter> screw2_transformPD =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();
		screw2_transformPD->SetTransform(screw_transform2);
		screw2_transformPD->SetInputData(this->m_style->screw_data);


		vtkSmartPointer<vtkPolyDataMapper> screw2_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		screw2_mapper->SetInputConnection(screw2_transformPD->GetOutputPort());


		vtkSmartPointer<vtkActor> screw2_actor =
			vtkSmartPointer<vtkActor>::New();
		screw2_actor->SetMapper(screw2_mapper);
		screw2_actor->GetProperty()->SetColor(0, 0.8, 0);
		screw2_actor->GetProperty()->SetOpacity(1);
		screw2_actor->SetVisibility(1);

		this->m_pRenderer->RemoveActor(this->m_style->actor_cone2);
		this->m_pRenderer->AddActor(screw2_actor);
		this->m_style->screw_actor2 = screw2_actor;
		this->operate_window->update();
		//std::cout << "path2 is ready!" << std::endl;


		/*vtkSmartPointer<vtkCylinderSource> path1_cylinder =
			vtkSmartPointer<vtkCylinderSource>::New();
		path1_cylinder->SetHeight(100);
		path1_cylinder->SetRadius(1);
		path1_cylinder->SetResolution(10);
		path1_cylinder->SetCenter(0, 0, 0);*/
		this->m_style->finalPath[9] = this->m_style->point->getPoint(1)[0];
		this->m_style->finalPath[10] = this->m_style->point->getPoint(1)[1];
		this->m_style->finalPath[11] = this->m_style->point->getPoint(1)[2];
		this->m_style->finalPath[9] = this->m_style->finalPath[6] + this->m_style->planeNormal[0] * this->m_style->middleLen;
		this->m_style->finalPath[10] = this->m_style->finalPath[7] + this->m_style->planeNormal[1] * this->m_style->middleLen;
		this->m_style->finalPath[11] = this->m_style->finalPath[8] + this->m_style->planeNormal[2] * this->m_style->middleLen;
		//double middle_origin_apex[3] = { 13.58, 14.08, 14.14 };
		vtkSmartPointer<vtkTransform> middle_transform =
			vtkSmartPointer<vtkTransform>::New();
		//double middle_dir_vector[3] = { dir_vectors[0],dir_vectors[1], dir_vectors[2] };


		double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
		vtkMath::Normalize(x_axis);


		double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

		double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
		if (rate < 0)
		{
			dir_vectors[0] = -dir_vectors[0] / rate;
			dir_vectors[1] = -dir_vectors[1] / rate;
			dir_vectors[2] = -dir_vectors[2] / rate;

			y_axis[0] = x_axis[0] + dir_vectors[0];
			y_axis[1] = x_axis[1] + dir_vectors[1];
			y_axis[2] = x_axis[2] + dir_vectors[2];
		}
		else if (rate > 0)
		{
			dir_vectors[0] = dir_vectors[0] / rate;
			dir_vectors[1] = dir_vectors[1] / rate;
			dir_vectors[2] = dir_vectors[2] / rate;

			y_axis[0] = -x_axis[0] + dir_vectors[0];
			y_axis[1] = -x_axis[1] + dir_vectors[1];
			y_axis[2] = -x_axis[2] + dir_vectors[2];
		}

		vtkMath::Normalize(y_axis);

		double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
							 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
							 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
		vtkMath::Normalize(z_axis);

		double matrix[16] = { x_axis[0], y_axis[0], z_axis[0], this->m_style->point->getPoint(1)[0],
							  x_axis[1], y_axis[1], z_axis[1], this->m_style->point->getPoint(1)[1],
							  x_axis[2], y_axis[2], z_axis[2], this->m_style->point->getPoint(1)[2],
							  0        , 0,          0,        1 };

		middle_transform->SetMatrix(matrix);

		middle_transform->Update();

		vtkSmartPointer<vtkTransformPolyDataFilter> middle_transformPD =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();
		middle_transformPD->SetTransform(middle_transform);
		middle_transformPD->SetInputData(this->m_style->base_data);

		vtkSmartPointer<vtkPolyDataMapper> middle_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		middle_mapper->SetInputConnection(middle_transformPD->GetOutputPort());

		vtkSmartPointer<vtkActor> middle_actor =
			vtkSmartPointer<vtkActor>::New();
		middle_actor->SetMapper(middle_mapper);
		middle_actor->GetProperty()->SetColor(0, 0.8, 0.8);
		middle_actor->GetProperty()->SetOpacity(1);
		middle_actor->SetVisibility(1);
		this->m_pRenderer->AddActor(middle_actor);
		//this->m_style->base_actor = middle_actor;



		vtkSmartPointer<vtkActorCollection> act_c1 =
			vtkSmartPointer<vtkActorCollection>::New();
		act_c1 = this->qvtkWidget_1->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors();
		int num1 = act_c1->GetNumberOfItems();
		act_c1->InitTraversal();
		for (int i = 0;i < num1;i++)
		{
			this->qvtkWidget_1->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(this->qvtkWidget_1->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors()->GetNextActor());
		}

		vtkSmartPointer<vtkActorCollection> act_c2 =
			vtkSmartPointer<vtkActorCollection>::New();
		act_c2 = this->qvtkWidget_2->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors();
		int num2 = act_c2->GetNumberOfItems();
		act_c2->InitTraversal();
		for (int i = 0;i < num2;i++)
		{
			this->qvtkWidget_2->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(this->qvtkWidget_2->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors()->GetNextActor());
		}


		vtkSmartPointer<vtkActorCollection> act_c3 =
			vtkSmartPointer<vtkActorCollection>::New();
		act_c3 = this->qvtkWidget_3->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors();
		int num3 = act_c3->GetNumberOfItems();
		act_c3->InitTraversal();
		for (int i = 0;i < num3;i++)
		{
			this->qvtkWidget_3->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(this->qvtkWidget_3->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors()->GetNextActor());
		}

		vtkSmartPointer<vtkAppendPolyData> append_fillter =
			vtkSmartPointer<vtkAppendPolyData>::New();
		append_fillter->AddInputConnection(screw1_transformPD->GetOutputPort());
		append_fillter->AddInputConnection(screw2_transformPD->GetOutputPort());
		append_fillter->Update();


		int extent[6];
		double spacing[3];
		double origin[3];
		this->m_style->boneIMGData->GetExtent(extent);
		this->m_style->boneIMGData->GetSpacing(spacing);
		this->m_style->boneIMGData->GetOrigin(origin);
		this->m_style->base_poly_data = middle_transformPD->GetOutput();
		this->m_style->screw1_poly_data = screw1_transformPD->GetOutput();
		this->m_style->screw2_poly_data = screw2_transformPD->GetOutput();

		int half[3] = { (extent[0] + extent[1]) ,(extent[2] + extent[3]) , (extent[4] + extent[5]) };

		this->m_style->callback1->setProsthesis(middle_transformPD->GetOutput(), screw1_transformPD->GetOutput(), screw2_transformPD->GetOutput(), 1);
		this->horizontalSlider_1->setEnabled(1);

		this->m_style->callback2->setProsthesis(middle_transformPD->GetOutput(), screw1_transformPD->GetOutput(), screw2_transformPD->GetOutput(), 1);
		this->horizontalSlider_2->setEnabled(1);

		this->m_style->callback3->setProsthesis(middle_transformPD->GetOutput(), screw1_transformPD->GetOutput(), screw2_transformPD->GetOutput(), 1);
		this->horizontalSlider_3->setEnabled(1);

		this->qvtkWidget_1->GetRenderWindow()->Render();
		this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
		this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
		this->qvtkWidget_1->update();

		this->qvtkWidget_2->GetRenderWindow()->Render();
		this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
		this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
		this->qvtkWidget_2->update();

		this->qvtkWidget_3->GetRenderWindow()->Render();
		this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
		this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
		this->qvtkWidget_3->update();

		QElapsedTimer et;
		et.start();
		while (et.elapsed() < 25)
		{
			QApplication::processEvents();
		}
		progressEnd();
		this->operate_window->update();
	}



	double  origin[3] = { 0 };
	double  spacing[3] = { 1 };
	this->m_style->boneIMGData->GetOrigin(origin);
	this->m_style->boneIMGData->GetSpacing(spacing);

	double dir_1[3] = { this->m_style->finalPath[3] - this->m_style->finalPath[0],
						this->m_style->finalPath[4] - this->m_style->finalPath[1],
						this->m_style->finalPath[5] - this->m_style->finalPath[2] };
	vtkMath::Normalize(dir_1);

	double dir_2[3] = { this->m_style->finalPath[9] - this->m_style->finalPath[6],
						this->m_style->finalPath[10] - this->m_style->finalPath[7],
						this->m_style->finalPath[11] - this->m_style->finalPath[8] };
	vtkMath::Normalize(dir_2);

	double dir_3[3] = { this->m_style->finalPath[15] - this->m_style->finalPath[12],
						this->m_style->finalPath[16] - this->m_style->finalPath[13],
						this->m_style->finalPath[17] - this->m_style->finalPath[14] };
	vtkMath::Normalize(dir_3);
	this->output_pte->appendPlainText("\n*************************************");
	this->output_pte->appendPlainText("--start point and end point of path 1:");
	QString path1_start = QString::number(this->m_style->finalPath[0]);// +m_style->patient_origin[0]);//(m_style->finalPath[0] - origin[0]) / spacing[0]));
	path1_start.append("  ");
	path1_start.append(QString::number(this->m_style->finalPath[1]));//2 * m_style->bone_center[1] - m_style->finalPath[1] + m_style->patient_origin[1]));//(((m_style->finalPath[1] - origin[1]) / spacing[1])));
	path1_start.append("  ");
	path1_start.append(QString::number(this->m_style->finalPath[2]));//2 * m_style->bone_center[2] - m_style->finalPath[2] + m_style->patient_origin[2]));//(((m_style->finalPath[2] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path1_start);
	this->result_table->setItem(0, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[0])));// +m_style->patient_origin[0])));
	this->result_table->setItem(0, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[1])));//2 * m_style->bone_center[1] - m_style->finalPath[1] + m_style->patient_origin[1])));
	this->result_table->setItem(0, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[2])));//2 * m_style->bone_center[2] - m_style->finalPath[2] + m_style->patient_origin[2])));


	QString path1_end = QString::number(this->m_style->finalPath[3]);// +m_style->patient_origin[0]);//(((m_style->finalPath[3] - origin[0]) / spacing[0]));
	path1_end.append("  ");
	path1_end.append(QString::number(this->m_style->finalPath[4]));//2 * m_style->bone_center[1] - m_style->finalPath[4] + m_style->patient_origin[1]));//(((m_style->finalPath[4] - origin[1]) / spacing[1])));
	path1_end.append("  ");
	path1_end.append(QString::number(this->m_style->finalPath[5]));//2 * m_style->bone_center[2] - m_style->finalPath[5] + m_style->patient_origin[2]));//(((m_style->finalPath[5] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path1_end);
	double angle_1 = acos(dir_1[0] * dir_2[0] + dir_1[1] * dir_2[1] + dir_1[2] * dir_2[2]) * 180 / acos(-1);
	this->result_table->setItem(1, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[3])));// +m_style->patient_origin[0])));
	this->result_table->setItem(1, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[4])));//2 * m_style->bone_center[1] - m_style->finalPath[4] + m_style->patient_origin[1])));
	this->result_table->setItem(1, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[5])));//2 * m_style->bone_center[2] - m_style->finalPath[5] + m_style->patient_origin[2])));

	QString path1_angle = "angle with middle screw(degree):";
	path1_angle.append(QString::number(angle_1));
	this->output_pte->appendPlainText(path1_angle);
	QString Hu1 = "bone density index:";
	Hu1.append(QString::number(double(this->optimalHu1 / this->maxHu1)));
	/*Hu1.append("\tmax gray value integral of all paths:");
	Hu1.append(QString::number(this->maxHu1));*/
	this->output_pte->appendPlainText(Hu1);
	//path1_angle.append("°");



	this->output_pte->appendPlainText("\n--start point and end point of path 2:");
	QString path2_start = QString::number(this->m_style->finalPath[6]);// +m_style->patient_origin[0]);//(((m_style->finalPath[6] - origin[0]) / spacing[0]));
	path2_start.append("  ");
	path2_start.append(QString::number(this->m_style->finalPath[7]));//2 * m_style->bone_center[1] - m_style->finalPath[7] + m_style->patient_origin[1]));//(((m_style->finalPath[7] - origin[1]) / spacing[1])));
	path2_start.append("  ");
	path2_start.append(QString::number(this->m_style->finalPath[8]));//2 * m_style->bone_center[2] - m_style->finalPath[8] + m_style->patient_origin[2]));//(((m_style->finalPath[8] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path2_start);
	this->result_table->setItem(2, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[6])));// +m_style->patient_origin[0])));
	this->result_table->setItem(2, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[7])));//2 * m_style->bone_center[1] - m_style->finalPath[7] + m_style->patient_origin[1])));
	this->result_table->setItem(2, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[8])));//2 * m_style->bone_center[2] - m_style->finalPath[8] + m_style->patient_origin[2])));

	QString path2_end = QString::number(this->m_style->finalPath[9]);// +m_style->patient_origin[0]);//(((m_style->finalPath[9] - origin[0]) / spacing[0]));
	path2_end.append("  ");
	path2_end.append(QString::number(this->m_style->finalPath[10]));//2 * m_style->bone_center[1] - m_style->finalPath[10] + m_style->patient_origin[1]));//(((m_style->finalPath[10] - origin[1]) / spacing[1])));
	path2_end.append("  ");
	path2_end.append(QString::number(this->m_style->finalPath[11]));//2 * m_style->bone_center[2] - m_style->finalPath[11] + m_style->patient_origin[2]));//((m_style->finalPath[11] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path2_end);
	this->result_table->setItem(3, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[9])));// +m_style->patient_origin[0])));
	this->result_table->setItem(3, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[10])));//2 * m_style->bone_center[1] - m_style->finalPath[10] + m_style->patient_origin[1])));
	this->result_table->setItem(3, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[11])));//2 * m_style->bone_center[2] - m_style->finalPath[11] + m_style->patient_origin[2])));



	this->output_pte->appendPlainText("\n--start point and end point of path 3:");
	QString path3_start = QString::number(this->m_style->finalPath[12]);// +m_style->patient_origin[0]);//(((m_style->finalPath[12] - origin[0]) / spacing[0]));
	path3_start.append("  ");
	path3_start.append(QString::number(this->m_style->finalPath[13]));//2 * m_style->bone_center[1] - m_style->finalPath[13] + m_style->patient_origin[1]));//(((m_style->finalPath[13] - origin[1]) / spacing[1])));
	path3_start.append("  ");
	path3_start.append(QString::number(this->m_style->finalPath[14]));//2 * m_style->bone_center[2] - m_style->finalPath[14] + m_style->patient_origin[2]));//(((m_style->finalPath[14] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path3_start);
	this->result_table->setItem(4, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[12])));// +m_style->patient_origin[0])));
	this->result_table->setItem(4, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[13])));//2 * m_style->bone_center[1] - m_style->finalPath[13] + m_style->patient_origin[1])));
	this->result_table->setItem(4, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[14])));//2 * m_style->bone_center[2] - m_style->finalPath[14] + m_style->patient_origin[2])));

	QString path3_end = QString::number(this->m_style->finalPath[15]);// +m_style->patient_origin[0]);//(((m_style->finalPath[15] - origin[0]) / spacing[0]));
	path3_end.append("  ");
	path3_end.append(QString::number(this->m_style->finalPath[16]));//2 * m_style->bone_center[1] - m_style->finalPath[16] + m_style->patient_origin[1]));//(((m_style->finalPath[16] - origin[1]) / spacing[1])));
	path3_end.append("  ");
	path3_end.append(QString::number(this->m_style->finalPath[17]));//2 * m_style->bone_center[2] - m_style->finalPath[17] + m_style->patient_origin[2]));//(((m_style->finalPath[17] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path3_end);
	this->result_table->setItem(5, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[15])));// +m_style->patient_origin[0])));
	this->result_table->setItem(5, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[16])));//2 * m_style->bone_center[1] - m_style->finalPath[16] + m_style->patient_origin[1])));
	this->result_table->setItem(5, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[17])));//2 * m_style->bone_center[2] - m_style->finalPath[17] + m_style->patient_origin[2])));

	double angle_3 = acos(dir_3[0] * dir_2[0] + dir_3[1] * dir_2[1] + dir_3[2] * dir_2[2]) * 180 / acos(-1);
	QString path3_angle = "angle with middle screw(degree):";
	path3_angle.append(QString::number(angle_3));
	//path3_angle.append("°");
	this->output_pte->appendPlainText(path3_angle);
	QString Hu2 = "bone density index:";
	Hu2.append(QString::number(double(this->optimalHu2 / this->maxHu2)));
	/*Hu2.append("\tmax gray value integral of all paths:");
	Hu2.append(QString::number(this->maxHu2));*/
	this->output_pte->appendPlainText(Hu2);



	//double angle_1_3 = acos(dir_3[0] * dir_1[0] + dir_3[1] * dir_1[1] + dir_3[2] * dir_1[2]) * 180 / acos(-1);
	//QString path1_3_angle = "\n--angle between long screws(degree):";
	//path1_3_angle.append(QString::number(angle_1_3));
	//path1_3_angle.append("\n");
	////path3_angle.append("°");
	//this->output_pte->appendPlainText(path1_3_angle);
	this->output_pte->appendPlainText("*************************************");
	this->undo_button->setEnabled(1);
	this->in_button->setEnabled(1);
	this->out_button->setEnabled(1);
	this->up_button->setEnabled(1);
	this->down_button->setEnabled(1);
	this->right_button->setEnabled(1);
	this->left_button->setEnabled(1);
	this->rebuild_button->setEnabled(1);
	this->seg_button->setEnabled(1);
	if (this->m_style->finish)
	{
		this->path1_widget->setEnabled(1);
		this->path3_widget->setEnabled(1);
	}
	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}
}



//void ProjectMainWindow::update_progress(int nNum)
//{
//	this->progressBar->setValue(nNum);
//}

void ProjectMainWindow::progressBegin()
{
	for (int i = 0;i < 2000;i++)
	{
		this->progressBar->setValue(i);
		//QThread::msleep(i / 10000);
	}
	//this->m_myThread.m_bStart = true;
	//this->m_myThread.start();
}

void ProjectMainWindow::progressMiddle()
{
	for (int i = 2000;i < 6001;i++)
	{
		this->progressBar->setValue(i);
		//QThread::msleep(i / 10000);
	}
	//this->m_myThread.m_bStart = true;
	//this->m_myThread.start();
}

void ProjectMainWindow::progressEnd()
{
	for (int i = 6001;i < 10000;i++)
	{

		//QThread::msleep((10000 - i) / 500);
		this->progressBar->setValue(i);
	}
	QThread::msleep(500);
	this->progressBar->setValue(0);
	//this->m_myThread.m_bStart = false;
	//this->m_myThread.start();
	//m_thread.stop();
}

void ProjectMainWindow::onRebuildDialog()
{
	QMessageBox* msg_box = new QMessageBox(this);
	msg_box->setAttribute(Qt::WA_DeleteOnClose);
	msg_box->setText("sure to rebuild?");;
	msg_box->setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
	int ret = msg_box->exec();
	switch (ret)
	{
	case QMessageBox::Cancel:
		break;
	case QMessageBox::Yes: {
		this->progressBegin();
		this->path1_widget->setEnabled(0);
		this->path3_widget->setEnabled(0);
		//this->m_style->boneExtractor->SetInputData(this->m_style->boneIMGData);
		this->m_style->boneExtractor->SetValue(0, this->marchingCubes_sb->value());
		//this->m_style->boneExtractor->ComputeNormalsOn();
		this->m_style->boneExtractor->Update();
		//this->m_style->boneExtractor->Modified();

		double* range = m_style->boneIMGData->GetScalarRange();
		//建立映射
		vtkSmartPointer<vtkLookupTable> lut =
			vtkSmartPointer<vtkLookupTable>::New();
		lut->SetHueRange(0.0, 0.6);
		lut->SetAlphaRange(1.0, 1.0);
		lut->SetValueRange(1.0, 1.0);
		lut->SetSaturationRange(1.0, 1.0);
		lut->SetNumberOfTableValues(256);
		lut->SetRange(range);
		lut->Build();

		this->threshold1_sb->setValue(this->m_style->CTValueNormalize(this->marchingCubes_sb->value()) - this->m_style->threshold_offset);
		this->threshold2_sb->setValue(this->m_style->CTValueNormalize(this->marchingCubes_sb->value()) - this->m_style->threshold_offset);

		this->progressMiddle();


		vtkSmartPointer <vtkPolyDataMapper> boneMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
		boneMapper->SetInputData(this->m_style->boneExtractor->GetOutput());
		boneMapper->SetLookupTable(lut);
		boneMapper->SetScalarRange(range);
		boneMapper->SetScalarVisibility(1);

		//建立角色
		vtkSmartPointer<vtkActor> bone = vtkSmartPointer<vtkActor>::New();
		bone->SetMapper(boneMapper);
		boneMapper->ScalarVisibilityOff();
		bone->GetProperty()->SetDiffuseColor(1, 0.9, 0.8);
		bone->GetProperty()->SetOpacity(1);
		bone->GetProperty()->ShadingOn();

		this->opacity_slider->setEnabled(true);
		this->opacity_slider->setMaximum(100);
		this->opacity_slider->setMinimum(0);
		this->opacity_slider->setValue(100);


		this->m_style->wholeBonePolyData = this->m_style->boneExtractor->GetOutput();
		this->m_style->bone_cur_actor = bone;
		this->m_style->bone_origin_actor = bone;


		/*vtkSmartPointer<vtkNamedColors> colours =
			vtkSmartPointer<vtkNamedColors>::New();
		double r = 0;
		double g = 0;
		double b = 0;
		colours->GetColor("Wheat", r, g, b);
		this->axesWidget->SetInteractor(operate_window->GetInteractor());
		this->axesWidget->SetViewport(0.0, 0.0, 0.2, 0.3);
		this->axesWidget->SetOutlineColor(r, g, b);
		this->axesWidget->SetEnabled(1);*/
		//this->axesWidget->InteractiveOn();



		this->path_button->setEnabled(true);
		this->clip_first_on->setEnabled(true);


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int extent[6];
		double spacing[3];
		double origin[3];

		this->m_style->boneIMGData->GetExtent(extent);
		this->m_style->boneIMGData->GetSpacing(spacing);
		this->m_style->boneIMGData->GetOrigin(origin);

		int half[3] = { (extent[0] + extent[1]) ,(extent[2] + extent[3]) , (extent[4] + extent[5]) };

		double center[3];
		center[0] = origin[0] + spacing[0] * 0.5 * half[0];
		center[1] = origin[1] + spacing[1] * 0.5 * half[1];
		center[2] = origin[2] + spacing[2] * 0.5 * half[2];

		static double sagittalElements[16] = {
			0, 0,-1, 0,
			1, 0, 0, 0,
			0,-1, 0, 0,
			0, 0, 0, 1 };

		static double cornalElements[16] = {
			1, 0, 0, 0,
			0, 0, 1, 0,
			0, -1,0, 0,
			0, 0, 0, 1 };


		static double obliqueElements[16] = {
			1, 0, 0, 0,
			0, 0.866025, -0.5, 0,
			0, 0.5, 0.866025, 0,
			0, 0, 0, 1 };


		static double axialElements[16] = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};

		double x[3] = { 1, 0, 0 };
		double y[3] = { 0, 1, 0 };
		double z[3] = { 0, 0, 1 };

		vtkSmartPointer<vtkMatrix4x4> resliceAxes1 =
			vtkSmartPointer<vtkMatrix4x4>::New();
		resliceAxes1->DeepCopy(axialElements);


		resliceAxes1->SetElement(0, 3, center[0]);
		resliceAxes1->SetElement(1, 3, center[1]);
		resliceAxes1->SetElement(2, 3, center[2]);

		vtkSmartPointer<vtkMatrix4x4> resliceAxes2 =
			vtkSmartPointer<vtkMatrix4x4>::New();
		resliceAxes2->DeepCopy(sagittalElements);

		resliceAxes2->SetElement(0, 3, center[0]);
		resliceAxes2->SetElement(1, 3, center[1]);
		resliceAxes2->SetElement(2, 3, center[2]);

		vtkSmartPointer<vtkMatrix4x4> resliceAxes3 =
			vtkSmartPointer<vtkMatrix4x4>::New();
		resliceAxes3->DeepCopy(cornalElements);

		resliceAxes3->SetElement(0, 3, center[0]);
		resliceAxes3->SetElement(1, 3, center[1]);
		resliceAxes3->SetElement(2, 3, center[2]);

		vtkSmartPointer<vtkImageReslice> reslice1 =
			vtkSmartPointer<vtkImageReslice>::New();
		reslice1->SetInputData(this->m_style->bone_img_reader->GetOutput());
		reslice1->SetOutputDimensionality(2);
		//#if 0
		reslice1->SetResliceAxes(resliceAxes1);
		//#else
			//reslice1->SetResliceAxesDirectionCosines(x, y, z);
			//reslice1->SetResliceAxesOrigin(center);
		//#endif
		reslice1->SetInterpolationModeToLinear();



		vtkSmartPointer<vtkImageReslice> reslice2 =
			vtkSmartPointer<vtkImageReslice>::New();
		reslice2->SetInputData(this->m_style->bone_img_reader->GetOutput());
		reslice2->SetOutputDimensionality(2);
		//#if 0
		reslice2->SetResliceAxes(resliceAxes2);
		//#else
		//	reslice2->SetResliceAxesDirectionCosines(x, y, z);
		//	reslice2->SetResliceAxesOrigin(center);
		//#endif
		reslice2->SetInterpolationModeToLinear();

		vtkSmartPointer<vtkImageReslice> reslice3 =
			vtkSmartPointer<vtkImageReslice>::New();
		reslice3->SetInputData(this->m_style->bone_img_reader->GetOutput());
		reslice3->SetOutputDimensionality(2);
		//#if 0
		reslice3->SetResliceAxes(resliceAxes3);
		//#else
		//	reslice3->SetResliceAxesDirectionCosines(x, y, z);
		//	reslice3->SetResliceAxesOrigin(center);
		//#endif
		reslice3->SetInterpolationModeToLinear();


		this->m_pRenderer->RemoveAllViewProps();
		this->m_pRenderer1->RemoveAllViewProps();
		this->m_style->callback1->contour_renderer->RemoveAllViewProps();
		this->m_pRenderer2->RemoveAllViewProps();
		this->m_style->callback2->contour_renderer->RemoveAllViewProps();
		this->m_pRenderer3->RemoveAllViewProps();
		this->m_style->callback3->contour_renderer->RemoveAllViewProps();


		vtkSmartPointer<vtkImageMapToColors> colorMap1 =
			vtkSmartPointer<vtkImageMapToColors>::New();
		colorMap1->SetLookupTable(this->m_style->colorTable);
		colorMap1->SetInputConnection(reslice1->GetOutputPort());
		colorMap1->Update();

		vtkSmartPointer<vtkImageMapToColors> colorMap2 =
			vtkSmartPointer<vtkImageMapToColors>::New();
		colorMap2->SetLookupTable(this->m_style->colorTable);
		colorMap2->SetInputConnection(reslice2->GetOutputPort());
		colorMap2->Update();

		vtkSmartPointer<vtkImageMapToColors> colorMap3 =
			vtkSmartPointer<vtkImageMapToColors>::New();
		colorMap3->SetLookupTable(this->m_style->colorTable);
		colorMap3->SetInputConnection(reslice3->GetOutputPort());
		colorMap3->Update();

		vtkSmartPointer<vtkImageActor> imgActor1 =
			vtkSmartPointer<vtkImageActor>::New();
		imgActor1->GetMapper()->SetInputConnection(colorMap1->GetOutputPort());
		//imgActor->SetInputData(colorMap->GetOutput());


		this->m_pRenderer->AddActor(bone);

		this->m_pRenderer1->AddActor(imgActor1);
		this->m_pRenderer1->SetBackground(0, 0, 0);

		vtkSmartPointer<vtkImageActor> imgActor2 =
			vtkSmartPointer<vtkImageActor>::New();
		imgActor2->GetMapper()->SetInputConnection(colorMap2->GetOutputPort());
		//imgActor->SetInputData(colorMap->GetOutput());


		this->m_pRenderer2->AddActor(imgActor2);
		this->m_pRenderer2->SetBackground(0, 0, 0);

		vtkSmartPointer<vtkImageActor> imgActor3 =
			vtkSmartPointer<vtkImageActor>::New();
		imgActor3->GetMapper()->SetInputConnection(colorMap3->GetOutputPort());
		//imgActor->SetInputData(colorMap->GetOutput());


		this->m_pRenderer3->AddActor(imgActor3);
		this->m_pRenderer3->SetBackground(0, 0, 0);



		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor1 =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		vtkSmartPointer<vtkInteractorStyleImage> imagestyle1 =
			vtkSmartPointer<vtkInteractorStyleImage>::New();;
		renderWindowInteractor1->SetInteractorStyle(imagestyle1);
		renderWindowInteractor1->SetRenderWindow(this->qvtkWidget_1->GetRenderWindow());


		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor2 =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		vtkSmartPointer<vtkInteractorStyleImage> imagestyle2 =
			vtkSmartPointer<vtkInteractorStyleImage>::New();
		renderWindowInteractor2->SetInteractorStyle(imagestyle2);
		renderWindowInteractor2->SetRenderWindow(this->qvtkWidget_2->GetRenderWindow());


		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor3 =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		vtkSmartPointer<vtkInteractorStyleImage> imagestyle3 =
			vtkSmartPointer<vtkInteractorStyleImage>::New();
		renderWindowInteractor3->SetInteractorStyle(imagestyle3);
		renderWindowInteractor3->SetRenderWindow(this->qvtkWidget_3->GetRenderWindow());




		this->m_style->callback1->SetImageReslice(reslice1);
		this->m_style->callback1->SetInteractor(renderWindowInteractor1);
		this->m_style->callback1->SetMapToColors(colorMap1);
		this->m_style->callback1->setImageData(this->m_style->boneIMGData, this->m_style->bone_center,this->m_pRenderer1,this->m_style);
		this->m_style->callback1->prosthesisOrNot = 0;
		//callback1->setFlag(0);
		this->m_style->callback1->SetRenderWindow(this->qvtkWidget_1->GetRenderWindow());
		imagestyle1->AddObserver(vtkCommand::MouseMoveEvent, this->m_style->callback1);
		imagestyle1->AddObserver(vtkCommand::LeftButtonPressEvent, this->m_style->callback1);
		imagestyle1->AddObserver(vtkCommand::LeftButtonReleaseEvent, this->m_style->callback1);
		//imagestyle1->AddObserver(vtkCommand::MiddleButtonPressEvent, this->m_style->callback1);
		//imagestyle1->AddObserver(vtkCommand::MiddleButtonReleaseEvent, this->m_style->callback1);
		//this->horizontalSlider_1->setEnabled(1);



		/*vtkSmartPointer<vtkImageInteractionCallback> callback2 =
			vtkSmartPointer<vtkImageInteractionCallback>::New();*/
		this->m_style->callback2->SetImageReslice(reslice2);
		this->m_style->callback2->SetInteractor(renderWindowInteractor2);
		this->m_style->callback2->SetMapToColors(colorMap2);
		this->m_style->callback2->setImageData(this->m_style->boneIMGData, this->m_style->bone_center,this->m_pRenderer2,this->m_style);
		this->m_style->callback2->prosthesisOrNot = 0;
		//callback2->setFlag(0);
		this->m_style->callback2->SetRenderWindow(this->qvtkWidget_2->GetRenderWindow());
		imagestyle2->AddObserver(vtkCommand::MouseMoveEvent, this->m_style->callback2);
		imagestyle2->AddObserver(vtkCommand::LeftButtonPressEvent, this->m_style->callback2);
		imagestyle2->AddObserver(vtkCommand::LeftButtonReleaseEvent, this->m_style->callback2);
		//imagestyle2->AddObserver(vtkCommand::MiddleButtonPressEvent, this->m_style->callback2);
		//imagestyle2->AddObserver(vtkCommand::MiddleButtonReleaseEvent, this->m_style->callback2);
		//this->horizontalSlider_2->setEnabled(1);


		/*vtkSmartPointer<vtkImageInteractionCallback> callback3 =
			vtkSmartPointer<vtkImageInteractionCallback>::New();*/
		this->m_style->callback3->SetImageReslice(reslice3);
		this->m_style->callback3->SetInteractor(renderWindowInteractor3);
		this->m_style->callback3->SetMapToColors(colorMap3);
		this->m_style->callback3->setImageData(this->m_style->boneIMGData, this->m_style->bone_center,this->m_pRenderer3,this->m_style);
		this->m_style->callback3->prosthesisOrNot = 0;
		//callback3->setFlag(0);
		this->m_style->callback3->SetRenderWindow(this->qvtkWidget_3->GetRenderWindow());
		imagestyle3->AddObserver(vtkCommand::MouseMoveEvent, this->m_style->callback3);
		imagestyle3->AddObserver(vtkCommand::LeftButtonPressEvent, this->m_style->callback3);
		imagestyle3->AddObserver(vtkCommand::LeftButtonReleaseEvent, this->m_style->callback3);
		//imagestyle3->AddObserver(vtkCommand::MiddleButtonPressEvent, this->m_style->callback3);
		//imagestyle3->AddObserver(vtkCommand::MiddleButtonReleaseEvent, this->m_style->callback3);
		//this->horizontalSlider_3->setEnabled(1);





		/// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




		this->operate_window->update();
		this->qvtkWidget_1->GetRenderWindow()->Render();
		this->m_pRenderer1->ResetCamera();
		this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
		this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
		this->qvtkWidget_1->update();

		this->qvtkWidget_2->GetRenderWindow()->Render();
		this->m_pRenderer2->ResetCamera();
		this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
		this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
		this->qvtkWidget_2->update();

		this->qvtkWidget_3->GetRenderWindow()->Render();
		this->m_pRenderer3->ResetCamera();
		this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
		this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
		this->qvtkWidget_3->update();


		this->operate_window->update();

		this->m_style->bone_cur_actor = bone;

		this->m_style->pointNum = 0;
		this->m_style->point->clear();
		this->m_style->planeOrNot = false;
		this->m_style->finish = false;


		QElapsedTimer et;
		et.start();
		while (et.elapsed() < 25)
		{
			QApplication::processEvents();
		}
		this->progressEnd();
		this->output_pte->appendPlainText("--rebuild successfully!");
		this->result_table->clearContents();
		break;
	}
	default:
		break;
	}

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}
	return;

	return;
}

void ProjectMainWindow::onSaveTXTDialog()
{
	vtkSmartPointer<vtkActorCollection> actors =
		vtkSmartPointer<vtkActorCollection>::New();
	actors = this->m_pRenderer->GetActors();//获取当前RENDER的ACTORS
	int iSum = actors->GetNumberOfItems();//获得这个渲染器内拥有的actor的数量
	actors->InitTraversal();//初始化访问便利链表，这两句话不可颠倒，初始化后获得的actor总数就不对了
	if (iSum <= 1)
		return;
	QString txt_save_path = QFileDialog::getSaveFileName(this, tr("save"), "../", "implant(*.implant)");
	if (txt_save_path.isEmpty())
	{
		QMessageBox::warning(this, tr("warning"), tr("can not find the path!"));
		this->output_pte->appendPlainText("\n--Fail to save the result!\n");
		return;
	}
	//txt_save_path.append(".txt");

	progressBegin();
	progressMiddle();
	// 支持带中文路径的读取
	QByteArray ba = txt_save_path.toLocal8Bit();
	const char* fileName_str = ba.data();

	QFile f(fileName_str);
	if (!f.open(QIODevice::Truncate | QIODevice::Text | QIODevice::ReadWrite | QIODevice::Append))
	{//追加写入 添加结束符\r\n
		QMessageBox::warning(this, tr("warning"), tr("can not find the path!"));
		return;
	}
	else
	{
		QString result = "3\n";
		for (int i = 0;i < 3;i++)
		{
			double color[3] = { 0 };
			color[i] = 1;
			result.append(QString::number(this->m_style->finalPath[6 * i]));
			result.append("  ");
			result.append(QString::number(this->m_style->finalPath[6 * i + 3]));
			result.append("  ");
			result.append(QString::number(color[0]));
			result.append("\n");
			result.append(QString::number(this->m_style->finalPath[6 * i + 1]));
			result.append("  ");
			result.append(QString::number(this->m_style->finalPath[6 * i + 4]));
			result.append("  ");
			result.append(QString::number(color[1]));
			result.append("\n");
			result.append(QString::number(this->m_style->finalPath[6 * i + 2]));
			result.append("  ");
			result.append(QString::number(this->m_style->finalPath[6 * i + 5]));
			result.append("  ");
			result.append(QString::number(color[2]));
			result.append("\n");
			if (i == 1)
			{
				result.append(QString::number(2*this->m_style->middle_radius));
				result.append(" ");
				result.append(QString::number(this->m_style->middleLen));
				result.append("\n");
			}
			else if (i == 0 || i == 2)
			{
				result.append(QString::number(2*this->m_style->screw_radius));
				result.append(" ");
				result.append(QString::number(this->m_style->screwLen));
				result.append("\n");
			}
		}

		/*vtkSmartPointer<vtkSphereSource> test_sphere1 = vtkSmartPointer<vtkSphereSource>::New();
		test_sphere1->SetCenter(this->m_style->finalPath[0], this->m_style->finalPath[1], this->m_style->finalPath[2]);
		test_sphere1->SetRadius(3);
		test_sphere1->Update();

		vtkSmartPointer<vtkPolyDataMapper> test_mapper1 = vtkSmartPointer<vtkPolyDataMapper>::New();
		test_mapper1->SetInputConnection(test_sphere1->GetOutputPort());

		vtkSmartPointer<vtkActor> test_actor1 = vtkSmartPointer<vtkActor>::New();
		test_actor1->SetMapper(test_mapper1);
		test_actor1->GetProperty()->SetColor(1, 0, 0);

		this->m_pRenderer->AddActor(test_actor1);
	
		vtkSmartPointer<vtkSphereSource> test_sphere2 = vtkSmartPointer<vtkSphereSource>::New();
		test_sphere2->SetCenter(this->m_style->finalPath[12], this->m_style->finalPath[13], this->m_style->finalPath[14]);
		test_sphere2->SetRadius(3);
		test_sphere2->Update();

		vtkSmartPointer<vtkPolyDataMapper> test_mapper2 = vtkSmartPointer<vtkPolyDataMapper>::New();
		test_mapper2->SetInputConnection(test_sphere2->GetOutputPort());

		vtkSmartPointer<vtkActor> test_actor2 = vtkSmartPointer<vtkActor>::New();
		test_actor2->SetMapper(test_mapper2);
		test_actor2->GetProperty()->SetColor(1, 0, 0);

		this->m_pRenderer->AddActor(test_actor2);*/

		QByteArray ba = result.toLocal8Bit();
		const char* data = ba.data();
		f.write(data);
	}
	f.close();
	QString info = "\n-Succeed in saving file:";
	info.append(fileName_str);
	info.append("!\n");
	this->output_pte->appendPlainText(info);


	progressEnd();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}
	return;
}

void ProjectMainWindow::onSaveOBJDialog()
{
	if (!this->m_style->finish)
		return;
	QString stl_save_path = QFileDialog::getSaveFileName(this, tr("save"), "../");
	if (stl_save_path.isEmpty())
	{
		QMessageBox::warning(this, tr("warning"), tr("can not find the path!"));
		this->output_pte->appendPlainText("\n--Fail to save STL file!\n");
		return;
	}

	progressBegin();

	//stl_save_path.append(".stl");

	// 支持带中文路径的读取
	QString screw1_stl_save_path = stl_save_path;
	screw1_stl_save_path.append("_screw1.stl");
	QByteArray ba1 = screw1_stl_save_path.toLocal8Bit();
	const char* screw1_fileName_str = ba1.data();

	//减少三角网格
	vtkSmartPointer<vtkTriangleFilter> screw1_stlFilter = vtkSmartPointer<vtkTriangleFilter>::New();//对polyData处理
	screw1_stlFilter->SetInputData(this->m_style->screw1_poly_data);

	//写出为STL格式
	vtkSmartPointer<vtkSTLWriter> screw1_stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
	screw1_stlWriter->SetFileName(screw1_fileName_str);
	screw1_stlWriter->SetInputConnection(screw1_stlFilter->GetOutputPort());
	screw1_stlWriter->Write();
	screw1_stlWriter->Update();
	QApplication::processEvents();

	QString screw2_stl_save_path = stl_save_path;
	screw2_stl_save_path.append("_screw2.stl");
	QByteArray ba2 = screw2_stl_save_path.toLocal8Bit();
	const char* screw2_fileName_str = ba2.data();

	vtkSmartPointer<vtkTriangleFilter> screw2_stlFilter = vtkSmartPointer<vtkTriangleFilter>::New();//对polyData处理
	screw2_stlFilter->SetInputData(this->m_style->screw2_poly_data);
	vtkSmartPointer<vtkSTLWriter> screw2_stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
	screw2_stlWriter->SetFileName(screw2_fileName_str);
	screw2_stlWriter->SetInputConnection(screw2_stlFilter->GetOutputPort());
	screw2_stlWriter->Write();
	screw2_stlWriter->Update();
	QApplication::processEvents();

	QString base_stl_save_path = stl_save_path;
	base_stl_save_path.append("_base.stl");
	QByteArray ba_base = base_stl_save_path.toLocal8Bit();
	const char* base_fileName_str = ba_base.data();

	//减少三角网格
	vtkSmartPointer<vtkTriangleFilter> base_stlFilter = vtkSmartPointer<vtkTriangleFilter>::New();//对polyData处理
	base_stlFilter->SetInputData(this->m_style->base_poly_data);

	//写出为STL格式
	vtkSmartPointer<vtkSTLWriter> base_stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
	base_stlWriter->SetFileName(base_fileName_str);
	base_stlWriter->SetInputConnection(base_stlFilter->GetOutputPort());
	base_stlWriter->Write();
	base_stlWriter->Update();
	QApplication::processEvents();

	progressMiddle();

	QString bone_stl_save_path = stl_save_path;
	bone_stl_save_path.append("_bone.stl");
	QByteArray ba_bone = bone_stl_save_path.toLocal8Bit();
	const char* bone_fileName_str = ba_bone.data();

	//减少三角网格
	
	vtkSmartPointer<vtkTriangleFilter> bone_stlFilter = vtkSmartPointer<vtkTriangleFilter>::New();//对polyData处理
	bone_stlFilter->SetInputData(this->m_style->curBonePolyData);

	//写出为STL格式
	vtkSmartPointer<vtkSTLWriter> bone_stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
	bone_stlWriter->SetFileName(bone_fileName_str);
	bone_stlWriter->SetInputConnection(bone_stlFilter->GetOutputPort());
	bone_stlWriter->Write();
	bone_stlWriter->Update();
	QApplication::processEvents();

	//QString all_stl_save_path = stl_save_path;
	//all_stl_save_path.append("_all.stl");
	//QByteArray ba_all = all_stl_save_path.toLocal8Bit();
	//const char* all_fileName_str = ba_all.data();

	////减少三角网格
	//vtkSmartPointer<vtkTriangleFilter> all_stlFilter = vtkSmartPointer<vtkTriangleFilter>::New();//对polyData处理
	//all_stlFilter->SetInputData(this->m_style->curBonePolyData);
	//all_stlFilter->AddInputData(this->m_style->base_poly_data);
	//all_stlFilter->AddInputData(this->m_style->screw2_poly_data);
	//all_stlFilter->AddInputData(this->m_style->screw1_poly_data);
	//all_stlFilter->Update();

	////写出为STL格式
	//vtkSmartPointer<vtkSTLWriter> all_stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
	//all_stlWriter->SetFileName(all_fileName_str);
	//all_stlWriter->SetInputConnection(all_stlFilter->GetOutputPort());
	//all_stlWriter->Write();
	//all_stlWriter->Update();
	QApplication::processEvents();



	QString info = "\n-Succeed in saving file:\n";
	info.append(screw1_fileName_str);
	info.append("!\n");
	info.append(screw2_fileName_str);
	info.append("!\n");
	info.append(base_fileName_str);
	info.append("!\n");
	info.append(bone_fileName_str);
	info.append("!\n");
	this->output_pte->appendPlainText(info);
   
	progressEnd();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}
	return;
}

void ProjectMainWindow::onReadmeDialog()
{
	QDialog* dialog = new QDialog(this);
	dialog->setModal(false);
	dialog->setWindowTitle("readme");
	dialog->setAttribute(Qt::WA_DeleteOnClose);
	QPlainTextEdit* readme = new QPlainTextEdit(dialog);
	//dialog->setFixedHeight(440);
	//dialog->setFixedWidth(570);//(QRect(8, 38, 445, 605));
	readme->setObjectName(QStringLiteral("readme"));
	QVBoxLayout* readme_ver = new QVBoxLayout(dialog);
	readme_ver->addWidget(readme);
	readme_ver->setContentsMargins(0, 0, 0, 0);
	//QHBoxLayout* readme_hor = new QHBoxLayout(dialog);
	//readme->setGeometry(QRect(10, 40, 441, 600));
	//readme->setSizeAdjustPolicy();
	QFont font6;
	font6.setPointSize(16);
	font6.setBold(true);
	font6.setWeight(75);
	readme->setFont(font6);
	readme->setFrameShape(QFrame::StyledPanel);
	readme->setFrameShadow(QFrame::Sunken);
	readme->setLineWidth(1);
	readme->setStyleSheet(QLatin1String("QMainWindow\n"
		"{\n"
		"    background-color:rgb(100, 40, 130);\n"
		"    \n"
		"}"));
	readme->appendPlainText("see file 'readme.txt' in the same path of this software! ");
	//readme->appendPlainText("一、简要说明：");
	//readme->appendPlainText("   该软件主要用于反置肩关节置换术术前规划，读取的文件类型是待手术病人DICOM文件夹。读取文件后建立病人骨骼的三维模型，再由软件操作者按照操作逻辑进行规划，并最终将结果可视化同时输出上中下三根螺钉的起点和终点坐标。");
	readme->setReadOnly(true);
	//readme->setContentsMargins(0, 0, 0, 0);
	/*QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	sizePolicy.setHorizontalStretch(0);
	sizePolicy.setVerticalStretch(0);
	sizePolicy.setHeightForWidth(readme->sizePolicy().hasHeightForWidth());
	readme->setSizePolicy(sizePolicy);
	readme->setFocusPolicy(Qt::ClickFocus);
	readme->setLayoutDirection(Qt::LeftToRight);*/
	//readme->setContentsMargins(0, 0, 0, 0);
	//readme->setAutoFillBackground(true);
	//dialog->setSize
	dialog->show();
}


void ProjectMainWindow::onRevisionDialog()
{
	QDialog* dialog = new QDialog(this);
	dialog->setModal(false);
	dialog->setWindowTitle("revision");
	QPushButton* angle_hor = new QPushButton(dialog);

	dialog->show();
}


void ProjectMainWindow::connect_first()
{
	if (this->seg_cbox->isChecked() == false)
	{
		this->output_pte->appendPlainText("--segmentation checkbox is off!");
		this->seg_button->setEnabled(false);
		return;
	}

	else
	{
		this->output_pte->appendPlainText("--segmentation checkbox is on!");
		this->seg_button->setEnabled(true);
	}
}

void ProjectMainWindow::segment()
{
	if (this->m_style->pointNum == 1)
	{
		progressBegin();
		vtkSmartPointer<vtkPolyDataConnectivityFilter> connectivityFilter =
			vtkSmartPointer<vtkPolyDataConnectivityFilter>::New();
		connectivityFilter->SetInputData(this->m_style->bone_cur_actor->GetMapper()->GetInput());
		connectivityFilter->SetExtractionModeToClosestPointRegion();
		connectivityFilter->SetClosestPoint(this->m_style->point->getPoint(1)[0], m_style->point->getPoint(1)[1], this->m_style->point->getPoint(1)[2]); //select the region to extract here
		connectivityFilter->Update();

		vtkSmartPointer<vtkAxesActor> axesActor =
			vtkSmartPointer<vtkAxesActor>::New();
		vtkSmartPointer<vtkOrientationMarkerWidget> axesWidget =
			vtkSmartPointer<vtkOrientationMarkerWidget>::New();
		axesWidget->SetOrientationMarker(axesActor);

		vtkSmartPointer<vtkNamedColors> colours =
			vtkSmartPointer<vtkNamedColors>::New();
		double r = 0;
		double g = 0;
		double b = 0;
		colours->GetColor("Wheat", r, g, b);
		axesWidget->SetInteractor(this->operate_window->GetRenderWindow()->GetInteractor());
		axesWidget->SetViewport(0.0, 0.0, 0.4, 0.4);
		axesWidget->SetOutlineColor(r, g, b);
		axesWidget->SetEnabled(1);
		axesWidget->InteractiveOn();

		/*vtkSmartPointer<vtkAxesActor> axesActor =
			vtkSmartPointer<vtkAxesActor>::New();
		axesActor->AxisLabelsOn();
		axesActor->SetDragable(0);
		axesActor->SetCylinderRadius(axesActor->GetCylinderRadius() * 2);
		axesActor->GetXAxisCaptionActor2D()->GetProperty()->SetColor(1, 0, 0);
		axesActor->GetYAxisCaptionActor2D()->GetProperty()->SetColor(0, 2, 0);
		axesActor->GetZAxisCaptionActor2D()->GetProperty()->SetColor(0, 0, 3);
		axesActor->SetConeRadius(axesActor->GetCylinderRadius());
		axesActor->SetTotalLength(70, 70, 70);
		m_pRenderer->AddActor(axesActor);*/

		progressMiddle();

		/*vtkSmartPointer<vtkSurfaceReconstructionFilter> surf =
			vtkSmartPointer<vtkSurfaceReconstructionFilter>::New();
		vtkSmartPointer<vtkPolyData> points =
			vtkSmartPointer<vtkPolyData>::New();
		points->SetPoints(connectivityFilter->GetOutput()->GetPoints());
		surf->SetInputData(points);
		surf->SetNeighborhoodSize(40);
		surf->SetSampleSpacing(0.005);

		vtkSmartPointer<vtkContourFilter> contour =
			vtkSmartPointer<vtkContourFilter>::New();
		contour->SetInputData(contour->GetOutput());
		contour->SetValue(0, 0.0);*/

		vtkSmartPointer<vtkPolyDataMapper> seg_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		seg_mapper->SetInputConnection(connectivityFilter->GetOutputPort());
		this->m_style->curBonePolyData = connectivityFilter->GetOutput();
		//m_style->bonePolyData = clip_data->GetOutput();



		vtkSmartPointer<vtkActor> seg_actor =
			vtkSmartPointer<vtkActor>::New();
		seg_actor->SetMapper(seg_mapper);
		seg_mapper->ScalarVisibilityOff();
		this->m_style->bone_cur_actor = seg_actor;
		//m_style->bonePolyData = seg_actor->GetMapper()->Get
		vtkSmartPointer<vtkNamedColors> colors =
			vtkSmartPointer<vtkNamedColors>::New();
		seg_actor->GetProperty()->SetDiffuseColor(1, 0.9, 0.8);
		//seg_actor->GetProperty()->SetDiffuse(0.0);
		//seg_actor->GetProperty()->SetSpecular(0.3);
		seg_actor->GetProperty()->ShadingOn();
		//bone->GetProperty()->SetSpecularPower(20);
		seg_actor->GetProperty()->SetOpacity(1);


		this->m_pRenderer->RemoveAllViewProps();
		//m_pRenderer->GetActors()->RemoveAllItems();
		this->m_pRenderer->AddActor(seg_actor);

		this->output_pte->appendPlainText("--segment finish!");

		//m_style->boneActor->GetMapper()->AddClippingPlane(plane);


		this->seg_button->setEnabled(false);
		this->seg_cbox->setChecked(false);

		this->m_style->point->deleteLastPoint();
		this->m_style->pointNum--;
		this->m_style->segmentOrNot = true;

		progressEnd();
		this->operate_window->update();
	}

	else return;
}


//void ProjectMainWindow::rightOrLeft()
//{
//	if (this->checkBox_l->isChecked())
//	{
//		//this->checkBox_l->setChecked(false);
//		this->checkBox_r->setChecked(false);
//
//	}
//
//	else if (this->checkBox_l->isChecked() == false)
//	{
//		this->checkBox_r->setChecked(true);
//	}
//
//
//	if (this->checkBox_l->isChecked())
//	{
//		this->output_pte->appendPlainText("--you are operating on left scapular!");
//	}
//	else
//	{
//		this->output_pte->appendPlainText("--you are operating on right scapular!");
//	}
//}


//void ProjectMainWindow::leftOrRight()
//{
//	if (this->checkBox_r->isChecked())
//	{
//		//this->checkBox_l->setChecked(false);
//		this->checkBox_l->setChecked(false);
//
//	}
//
//	else if (this->checkBox_r->isChecked() == false)
//	{
//		this->checkBox_l->setChecked(true);
//	}
//
//	if (this->checkBox_l->isChecked())
//	{
//		this->output_pte->appendPlainText("--you are operating on left scapular!");
//	}
//	else
//	{
//		this->output_pte->appendPlainText("--you are operating on right scapular!");
//	}
//}


void ProjectMainWindow::ajustOpacity()
{
	this->m_style->bone_cur_actor->GetProperty()->SetOpacity(this->opacity_slider->value() / double(100));
	this->operate_window->update();

	//this->output_pte->appendPlainText(QString::number(this->opacity_slider->value() / double(100)));
}


void ProjectMainWindow::min_slider_window_syn()
{
	int min_v = this->minWinWid->value();
	int max_v = this->maxWinWid->value();
	this->window_min_width->setValue(min_v);
	this->m_style->colorTable->SetRange(vtkMath::Min(min_v, max_v), vtkMath::Max(min_v, max_v));
	this->qvtkWidget_1->update();
	this->qvtkWidget_2->update();
	this->qvtkWidget_3->update();
}


void ProjectMainWindow::min_box_window_syn()
{
	int min_v = this->window_min_width->value();
	int max_v = this->window_max_width->value();
	this->minWinWid->setValue(min_v);
	this->m_style->colorTable->SetRange(vtkMath::Min(min_v, max_v), vtkMath::Max(min_v, max_v));
	this->qvtkWidget_1->update();
	this->qvtkWidget_2->update();
	this->qvtkWidget_3->update();
}

void ProjectMainWindow::max_slider_window_syn()
{
	int min_v = this->minWinWid->value();
	int max_v = this->maxWinWid->value();
	this->window_max_width->setValue(max_v);
	this->m_style->colorTable->SetRange(vtkMath::Min(min_v, max_v), vtkMath::Max(min_v, max_v));
	this->qvtkWidget_1->update();
	this->qvtkWidget_2->update();
	this->qvtkWidget_3->update();
}


void ProjectMainWindow::max_box_window_syn()
{
	int min_v = this->window_min_width->value();
	int max_v = this->window_max_width->value();
	this->maxWinWid->setValue(max_v);
	this->m_style->colorTable->SetRange(vtkMath::Min(min_v, max_v), vtkMath::Max(min_v, max_v));
	this->qvtkWidget_1->update();
	this->qvtkWidget_2->update();
	this->qvtkWidget_3->update();
}

void ProjectMainWindow::setSlice1()
{
	this->horizontalSlider_1->setValue(0);
	/*int Y = this->m_style->boneIMGData->GetDimensions()[1];
	double spacing = this->callback1->ImageReslice->GetOutput()->GetSpacing()[2];
	double deltaY = double((this->horizontalSlider_1->value() - this->curSlice1)) * Y / 100;
	this->curSlice1 = horizontalSlider_1->value();

	vtkMatrix4x4* matrix = this->callback1->ImageReslice->GetResliceAxes();
	double point[4], center[4];
	point[0] = 0.0;
	point[1] = 0.0;
	point[2] = spacing * deltaY;
	point[3] = 1.0;

	matrix->MultiplyPoint(point, center);
	matrix->SetElement(0, 3, center[0]);
	matrix->SetElement(1, 3, center[1]);
	matrix->SetElement(2, 3, center[2]);
	this->callback1->Interactor->Render();
	this->callback1->ImageReslice->Update();*/
}

void ProjectMainWindow::setSlice2()
{
	this->horizontalSlider_2->setValue(0);
	/*int Y = this->m_style->boneIMGData->GetDimensions()[1];
	double spacing = this->callback2->ImageReslice->GetOutput()->GetSpacing()[2];
	double deltaY = double((this->horizontalSlider_2->value() - this->curSlice2)) * Y / 100;
	this->curSlice2 = horizontalSlider_2->value();

	vtkMatrix4x4* matrix = this->callback2->ImageReslice->GetResliceAxes();
	double point[4], center[4];
	point[0] = 0.0;
	point[1] = 0.0;
	point[2] = spacing * deltaY;
	point[3] = 1.0;

	matrix->MultiplyPoint(point, center);
	matrix->SetElement(0, 3, center[0]);
	matrix->SetElement(1, 3, center[1]);
	matrix->SetElement(2, 3, center[2]);
	this->callback2->Interactor->Render();
	this->callback2->ImageReslice->Update();*/
}

void ProjectMainWindow::setSlice3()
{
	this->horizontalSlider_3->setValue(0);
	/*int Y = this->m_style->boneIMGData->GetDimensions()[1];
	double spacing = this->callback3->ImageReslice->GetOutput()->GetSpacing()[2];
	double deltaY = double((this->horizontalSlider_3->value() - this->curSlice3)) * Y / 100;
	this->curSlice3 = horizontalSlider_3->value();

	vtkMatrix4x4* matrix = this->callback3->ImageReslice->GetResliceAxes();
	double point[4], center[4];
	point[0] = 0.0;
	point[1] = 0.0;
	point[2] = spacing * deltaY;
	point[3] = 1.0;

	matrix->MultiplyPoint(point, center);
	matrix->SetElement(0, 3, center[0]);
	matrix->SetElement(1, 3, center[1]);
	matrix->SetElement(2, 3, center[2]);
	this->callback3->Interactor->Render();
	this->callback3->ImageReslice->Update();*/
}

void ProjectMainWindow::in_revision()
{
	if (this->m_style->pointNum != 7 || this->m_style->finish)
		return;
	double in_vector[3] = { this->m_style->planeNormal[0] * 0.3,this->m_style->planeNormal[1] * 0.3,this->m_style->planeNormal[2] * 0.3 };
	double newPoint1[3] = { this->m_style->point->getPoint(1)[0] + in_vector[0],this->m_style->point->getPoint(1)[1] + in_vector[1],this->m_style->point->getPoint(1)[2] + in_vector[2] };
	double newPoint4[3] = { this->m_style->point->getPoint(4)[0] + in_vector[0],this->m_style->point->getPoint(4)[1] + in_vector[1],this->m_style->point->getPoint(4)[2] + in_vector[2] };
	double newPoint6[3] = { this->m_style->point->getPoint(6)[0] + in_vector[0],this->m_style->point->getPoint(6)[1] + in_vector[1],this->m_style->point->getPoint(6)[2] + in_vector[2] };
	double newPoint7[3] = { this->m_style->point->getPoint(7)[0] + in_vector[0],this->m_style->point->getPoint(7)[1] + in_vector[1],this->m_style->point->getPoint(7)[2] + in_vector[2] };
	this->m_style->point->changePoint(1, newPoint1);
	this->m_style->point->changePoint(4, newPoint4);
	this->m_style->point->changePoint(6, newPoint6);
	this->m_style->point->changePoint(7, newPoint7);
	this->m_style->plane_actor->AddPosition(in_vector);
	this->m_style->middle_point_actor->AddPosition(in_vector);
	this->m_style->actor_cone1->AddPosition(in_vector);
	this->m_style->actor_cone2->AddPosition(in_vector);
	this->m_style->base_actor->AddPosition(in_vector);
	this->operate_window->update();
}

void ProjectMainWindow::out_revision()
{
	if (this->m_style->pointNum != 7 || this->m_style->finish)
		return;
	double out_vector[3] = { -this->m_style->planeNormal[0] * 0.3, -this->m_style->planeNormal[1] * 0.3, -this->m_style->planeNormal[2] * 0.3 };
	double newPoint1[3] = { this->m_style->point->getPoint(1)[0] + out_vector[0], this->m_style->point->getPoint(1)[1] + out_vector[1], this->m_style->point->getPoint(1)[2] + out_vector[2] };
	double newPoint4[3] = { this->m_style->point->getPoint(4)[0] + out_vector[0], this->m_style->point->getPoint(4)[1] + out_vector[1], this->m_style->point->getPoint(4)[2] + out_vector[2] };
	double newPoint6[3] = { this->m_style->point->getPoint(6)[0] + out_vector[0], this->m_style->point->getPoint(6)[1] + out_vector[1], this->m_style->point->getPoint(6)[2] + out_vector[2] };
	double newPoint7[3] = { this->m_style->point->getPoint(7)[0] + out_vector[0], this->m_style->point->getPoint(7)[1] + out_vector[1], this->m_style->point->getPoint(7)[2] + out_vector[2] };
	this->m_style->point->changePoint(1, newPoint1);
	this->m_style->point->changePoint(4, newPoint4);
	this->m_style->point->changePoint(6, newPoint6);
	this->m_style->point->changePoint(7, newPoint7);
	this->m_style->plane_actor->AddPosition(out_vector);
	this->m_style->middle_point_actor->AddPosition(out_vector);
	this->m_style->actor_cone1->AddPosition(out_vector);
	this->m_style->actor_cone2->AddPosition(out_vector);
	this->m_style->base_actor->AddPosition(out_vector);
	this->operate_window->update();
}

void ProjectMainWindow::up_revision()
{
	if (this->m_style->pointNum != 7 || this->m_style->finish)
		return;

	double up_vector[3] = { (this->m_style->point->getPoint(1)[0] - this->m_style->point->getPoint(4)[0]) ,
							(this->m_style->point->getPoint(1)[1] - this->m_style->point->getPoint(4)[1]) ,
							(this->m_style->point->getPoint(1)[2] - this->m_style->point->getPoint(4)[2]) };
	vtkMath::Normalize(up_vector);
	up_vector[0] = up_vector[0] * 0.3;
	up_vector[1] = up_vector[1] * 0.3;
	up_vector[2] = up_vector[2] * 0.3;

	double newPoint1[3] = { this->m_style->point->getPoint(1)[0] + up_vector[0], this->m_style->point->getPoint(1)[1] + up_vector[1], this->m_style->point->getPoint(1)[2] + up_vector[2] };
	double newPoint4[3] = { this->m_style->point->getPoint(4)[0] + up_vector[0], this->m_style->point->getPoint(4)[1] + up_vector[1], this->m_style->point->getPoint(4)[2] + up_vector[2] };
	double newPoint6[3] = { this->m_style->point->getPoint(6)[0] + up_vector[0], this->m_style->point->getPoint(6)[1] + up_vector[1], this->m_style->point->getPoint(6)[2] + up_vector[2] };
	double newPoint7[3] = { this->m_style->point->getPoint(7)[0] + up_vector[0], this->m_style->point->getPoint(7)[1] + up_vector[1], this->m_style->point->getPoint(7)[2] + up_vector[2] };
	this->m_style->point->changePoint(1, newPoint1);
	this->m_style->point->changePoint(4, newPoint4);
	this->m_style->point->changePoint(6, newPoint6);
	this->m_style->point->changePoint(7, newPoint7);
	this->m_style->plane_actor->AddPosition(up_vector);
	this->m_style->middle_point_actor->AddPosition(up_vector);
	this->m_style->actor_cone1->AddPosition(up_vector);
	this->m_style->actor_cone2->AddPosition(up_vector);
	this->m_style->base_actor->AddPosition(up_vector);

	this->operate_window->update();
}

void ProjectMainWindow::down_revision()
{
	if (this->m_style->pointNum != 7 || this->m_style->finish)
		return;

	double down_vector[3] = { -(this->m_style->point->getPoint(1)[0] - this->m_style->point->getPoint(4)[0]) ,
							  -(this->m_style->point->getPoint(1)[1] - this->m_style->point->getPoint(4)[1]) ,
							  -(this->m_style->point->getPoint(1)[2] - this->m_style->point->getPoint(4)[2]) };
	vtkMath::Normalize(down_vector);
	down_vector[0] = down_vector[0] * 0.3;
	down_vector[1] = down_vector[1] * 0.3;
	down_vector[2] = down_vector[2] * 0.3;
	double newPoint1[3] = { this->m_style->point->getPoint(1)[0] + down_vector[0], this->m_style->point->getPoint(1)[1] + down_vector[1], this->m_style->point->getPoint(1)[2] + down_vector[2] };
	double newPoint4[3] = { this->m_style->point->getPoint(4)[0] + down_vector[0], this->m_style->point->getPoint(4)[1] + down_vector[1], this->m_style->point->getPoint(4)[2] + down_vector[2] };
	double newPoint6[3] = { this->m_style->point->getPoint(6)[0] + down_vector[0], this->m_style->point->getPoint(6)[1] + down_vector[1], this->m_style->point->getPoint(6)[2] + down_vector[2] };
	double newPoint7[3] = { this->m_style->point->getPoint(7)[0] + down_vector[0], this->m_style->point->getPoint(7)[1] + down_vector[1], this->m_style->point->getPoint(7)[2] + down_vector[2] };
	this->m_style->point->changePoint(1, newPoint1);
	this->m_style->point->changePoint(4, newPoint4);
	this->m_style->point->changePoint(6, newPoint6);
	this->m_style->point->changePoint(7, newPoint7);
	this->m_style->plane_actor->AddPosition(down_vector);
	this->m_style->middle_point_actor->AddPosition(down_vector);
	this->m_style->actor_cone1->AddPosition(down_vector);
	this->m_style->actor_cone2->AddPosition(down_vector);
	this->m_style->base_actor->AddPosition(down_vector);

	this->operate_window->update();
}

void ProjectMainWindow::left_revision()
{
	if (this->m_style->pointNum != 7 || this->m_style->finish)
		return;

	double dir_vector[3] = { (this->m_style->point->getPoint(1)[0] - this->m_style->point->getPoint(4)[0]) ,
							 (this->m_style->point->getPoint(1)[1] - this->m_style->point->getPoint(4)[1]) ,
							 (this->m_style->point->getPoint(1)[2] - this->m_style->point->getPoint(4)[2]) };

	double left_vector[3] = { this->m_style->planeNormal[1] * dir_vector[2] - this->m_style->planeNormal[2] * dir_vector[1],
							  this->m_style->planeNormal[2] * dir_vector[0] - this->m_style->planeNormal[0] * dir_vector[2],
							  this->m_style->planeNormal[0] * dir_vector[1] - this->m_style->planeNormal[1] * dir_vector[0], };
	vtkMath::Normalize(left_vector);
	left_vector[0] = -left_vector[0] * 0.3;
	left_vector[1] = -left_vector[1] * 0.3;
	left_vector[2] = -left_vector[2] * 0.3;
	double newPoint1[3] = { this->m_style->point->getPoint(1)[0] + left_vector[0], this->m_style->point->getPoint(1)[1] + left_vector[1], this->m_style->point->getPoint(1)[2] + left_vector[2] };
	double newPoint4[3] = { this->m_style->point->getPoint(4)[0] + left_vector[0], this->m_style->point->getPoint(4)[1] + left_vector[1], this->m_style->point->getPoint(4)[2] + left_vector[2] };
	double newPoint6[3] = { this->m_style->point->getPoint(6)[0] + left_vector[0], this->m_style->point->getPoint(6)[1] + left_vector[1], this->m_style->point->getPoint(6)[2] + left_vector[2] };
	double newPoint7[3] = { this->m_style->point->getPoint(7)[0] + left_vector[0], this->m_style->point->getPoint(7)[1] + left_vector[1], this->m_style->point->getPoint(7)[2] + left_vector[2] };
	this->m_style->point->changePoint(1, newPoint1);
	this->m_style->point->changePoint(4, newPoint4);
	this->m_style->point->changePoint(6, newPoint6);
	this->m_style->point->changePoint(7, newPoint7);
	this->m_style->plane_actor->AddPosition(left_vector);
	this->m_style->middle_point_actor->AddPosition(left_vector);
	this->m_style->actor_cone1->AddPosition(left_vector);
	this->m_style->actor_cone2->AddPosition(left_vector);
	this->m_style->base_actor->AddPosition(left_vector);

	this->operate_window->update();
}

void ProjectMainWindow::right_revision()
{
	if (this->m_style->pointNum != 7 || this->m_style->finish)
		return;

	double dir_vector[3] = { (this->m_style->point->getPoint(1)[0] - this->m_style->point->getPoint(4)[0]) ,
							 (this->m_style->point->getPoint(1)[1] - this->m_style->point->getPoint(4)[1]) ,
							 (this->m_style->point->getPoint(1)[2] - this->m_style->point->getPoint(4)[2]) };

	double right_vector[3] = { this->m_style->planeNormal[1] * dir_vector[2] - this->m_style->planeNormal[2] * dir_vector[1],
							   this->m_style->planeNormal[2] * dir_vector[0] - this->m_style->planeNormal[0] * dir_vector[2],
							   this->m_style->planeNormal[0] * dir_vector[1] - this->m_style->planeNormal[1] * dir_vector[0], };
	vtkMath::Normalize(right_vector);
	right_vector[0] = right_vector[0] * 0.3;
	right_vector[1] = right_vector[1] * 0.3;
	right_vector[2] = right_vector[2] * 0.3;
	double newPoint1[3] = { this->m_style->point->getPoint(1)[0] + right_vector[0], this->m_style->point->getPoint(1)[1] + right_vector[1], this->m_style->point->getPoint(1)[2] + right_vector[2] };
	double newPoint4[3] = { this->m_style->point->getPoint(4)[0] + right_vector[0], this->m_style->point->getPoint(4)[1] + right_vector[1], this->m_style->point->getPoint(4)[2] + right_vector[2] };
	double newPoint6[3] = { this->m_style->point->getPoint(6)[0] + right_vector[0], this->m_style->point->getPoint(6)[1] + right_vector[1], this->m_style->point->getPoint(6)[2] + right_vector[2] };
	double newPoint7[3] = { this->m_style->point->getPoint(7)[0] + right_vector[0], this->m_style->point->getPoint(7)[1] + right_vector[1], this->m_style->point->getPoint(7)[2] + right_vector[2] };
	this->m_style->point->changePoint(1, newPoint1);
	this->m_style->point->changePoint(4, newPoint4);
	this->m_style->point->changePoint(6, newPoint6);
	this->m_style->point->changePoint(7, newPoint7);
	this->m_style->plane_actor->AddPosition(right_vector);
	this->m_style->middle_point_actor->AddPosition(right_vector);
	this->m_style->actor_cone1->AddPosition(right_vector);
	this->m_style->actor_cone2->AddPosition(right_vector);
	this->m_style->base_actor->AddPosition(right_vector);

	this->operate_window->update();
}



void ProjectMainWindow::l_r_revision()
{
	if (this->m_style->pointNum > 7 || this->m_style->finish)
	{
		this->l_r_scrollbar->setValue(this->l_r_box->value());
		return;
	}
	else if (this->m_style->pointNum < 7)
	{
		this->l_r_scrollbar->setValue(0);
		this->l_r_box->setValue(0);
		return;
	}


	double angle = double(this->l_r_scrollbar->value()) - double(this->l_r_box->value());
	this->l_r_box->setValue(this->l_r_scrollbar->value());

	if (angle == 0)
		return;



	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);


	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);


	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };


	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);

	double* origin = this->m_style->base_actor->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};

	this->m_style->plane_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone1->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone2->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->RotateWXYZ(angle, y_axis[0], y_axis[1], y_axis[2]);
	this->m_style->plane_actor->RotateWXYZ(angle, y_axis[0], y_axis[1], y_axis[2]);
	this->m_style->actor_cone1->RotateWXYZ(angle, y_axis[0], y_axis[1], y_axis[2]);
	this->m_style->actor_cone2->RotateWXYZ(angle, y_axis[0], y_axis[1], y_axis[2]);
	this->m_style->base_actor->SetOrigin(origin);
	this->m_style->plane_actor->SetOrigin(origin);
	this->m_style->actor_cone1->SetOrigin(origin);
	this->m_style->actor_cone2->SetOrigin(origin);

	angle = -angle * acos(-1) / 180;
	double rotateMatrix[3][3] =
	{ pow(y_axis[0],2) * (1 - cos(angle)) + cos(angle),y_axis[0] * y_axis[1] * (1 - cos(angle)) + y_axis[2] * sin(angle),y_axis[0] * y_axis[2] * (1 - cos(angle)) - y_axis[1] * sin(angle),

	  y_axis[0] * y_axis[1] * (1 - cos(angle)) - y_axis[2] * sin(angle),pow(y_axis[1],2) * (1 - cos(angle)) + cos(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) + y_axis[0] * sin(angle),

	  y_axis[0] * y_axis[2] * (1 - cos(angle)) + y_axis[1] * sin(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) - y_axis[0] * sin(angle), pow(y_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	this->m_style->planeNormal[0] = rotateMatrix[0][0] * x_axis[0] + rotateMatrix[0][1] * x_axis[1] + rotateMatrix[0][2] * x_axis[2];
	this->m_style->planeNormal[1] = rotateMatrix[1][0] * x_axis[0] + rotateMatrix[1][1] * x_axis[1] + rotateMatrix[1][2] * x_axis[2];
	this->m_style->planeNormal[2] = rotateMatrix[2][0] * x_axis[0] + rotateMatrix[2][1] * x_axis[1] + rotateMatrix[2][2] * x_axis[2];

	this->operate_window->update();
}

void ProjectMainWindow::u_d_revision()
{
	if (this->m_style->pointNum > 7 || this->m_style->finish)
	{
		this->u_d_scrollbar->setValue(this->u_d_box->value());
		return;
	}
	else if (this->m_style->pointNum < 7)
	{
		this->u_d_scrollbar->setValue(0);
		this->u_d_box->setValue(0);
		return;
	}

	double angle = double(this->u_d_scrollbar->value()) - double(this->u_d_box->value());
	this->u_d_box->setValue(this->u_d_scrollbar->value());

	if (angle == 0)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);


	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);


	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };


	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double* origin = this->m_style->base_actor->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};

	this->m_style->plane_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone1->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone2->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->RotateWXYZ(angle, z_axis[0], z_axis[1], z_axis[2]);
	this->m_style->plane_actor->RotateWXYZ(angle, z_axis[0], z_axis[1], z_axis[2]);
	this->m_style->actor_cone1->RotateWXYZ(angle, z_axis[0], z_axis[1], z_axis[2]);
	this->m_style->actor_cone2->RotateWXYZ(angle, z_axis[0], z_axis[1], z_axis[2]);
	this->m_style->base_actor->SetOrigin(origin);
	this->m_style->plane_actor->SetOrigin(origin);
	this->m_style->actor_cone1->SetOrigin(origin);
	this->m_style->actor_cone2->SetOrigin(origin);

	angle = -angle * acos(-1) / 180;
	double rotateMatrix[3][3] =
	{ pow(z_axis[0],2) * (1 - cos(angle)) + cos(angle),z_axis[0] * z_axis[1] * (1 - cos(angle)) + z_axis[2] * sin(angle),z_axis[0] * z_axis[2] * (1 - cos(angle)) - z_axis[1] * sin(angle),

	 z_axis[0] * z_axis[1] * (1 - cos(angle)) - z_axis[2] * sin(angle),pow(z_axis[1],2) * (1 - cos(angle)) + cos(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) + z_axis[0] * sin(angle),

	 z_axis[0] * z_axis[2] * (1 - cos(angle)) + z_axis[1] * sin(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) - z_axis[0] * sin(angle), pow(z_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	this->m_style->planeNormal[0] = rotateMatrix[0][0] * x_axis[0] + rotateMatrix[0][1] * x_axis[1] + rotateMatrix[0][2] * x_axis[2];
	this->m_style->planeNormal[1] = rotateMatrix[1][0] * x_axis[0] + rotateMatrix[1][1] * x_axis[1] + rotateMatrix[1][2] * x_axis[2];
	this->m_style->planeNormal[2] = rotateMatrix[2][0] * x_axis[0] + rotateMatrix[2][1] * x_axis[1] + rotateMatrix[2][2] * x_axis[2];

	double new_dir_vector[3] = { rotateMatrix[0][0] * y_axis[0] + rotateMatrix[0][1] * y_axis[1] + rotateMatrix[0][2] * y_axis[2],
								 rotateMatrix[1][0] * y_axis[0] + rotateMatrix[1][1] * y_axis[1] + rotateMatrix[1][2] * y_axis[2],
								 rotateMatrix[2][0] * y_axis[0] + rotateMatrix[2][1] * y_axis[1] + rotateMatrix[2][2] * y_axis[2] };

	double new_point4[3] = { this->m_style->point->getPoint(1)[0] + new_dir_vector[0],
							 this->m_style->point->getPoint(1)[1] + new_dir_vector[1],
							 this->m_style->point->getPoint(1)[2] + new_dir_vector[2] };

	double new_point6[3] = { this->m_style->point->getPoint(1)[0] - new_dir_vector[0] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[0],
							 this->m_style->point->getPoint(1)[1] - new_dir_vector[1] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[1],
							 this->m_style->point->getPoint(1)[2] - new_dir_vector[2] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[2] };

	double new_point7[3] = { this->m_style->point->getPoint(1)[0] + new_dir_vector[0] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[0],
							 this->m_style->point->getPoint(1)[1] + new_dir_vector[1] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[1],
							 this->m_style->point->getPoint(1)[2] + new_dir_vector[2] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[2] };

	this->m_style->point->changePoint(4, new_point4);
	this->m_style->point->changePoint(6, new_point6);
	this->m_style->point->changePoint(7, new_point7);


	this->operate_window->update();
}

void ProjectMainWindow::spin_revision()
{
	if (this->m_style->pointNum > 7 || this->m_style->finish)
	{
		this->spin_scrollbar->setValue(this->spin_box->value());
		return;
	}
	else if (this->m_style->pointNum < 7)
	{
		this->spin_scrollbar->setValue(0);
		this->spin_box->setValue(0);
		return;
	}

	double angle = double(this->spin_scrollbar->value()) - double(this->spin_box->value());
	this->spin_box->setValue(this->spin_scrollbar->value());
	if (angle == 0)
		return;

	double* last_origin = this->m_style->base_actor->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[2]};

	this->m_style->base_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone1->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone2->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->RotateWXYZ(angle, this->m_style->planeNormal[0], this->m_style->planeNormal[1], this->m_style->planeNormal[2]);
	this->m_style->actor_cone1->RotateWXYZ(angle, this->m_style->planeNormal[0], this->m_style->planeNormal[1], this->m_style->planeNormal[2]);
	this->m_style->actor_cone2->RotateWXYZ(angle, this->m_style->planeNormal[0], this->m_style->planeNormal[1], this->m_style->planeNormal[2]);
	this->m_style->base_actor->SetOrigin(last_origin);// [0] , origin[1], origin[2]);
	this->m_style->actor_cone1->SetOrigin(last_origin);
	this->m_style->actor_cone2->SetOrigin(last_origin);


	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);


	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);

	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);



	angle = -angle * acos(-1) / 180;



	double rotateMatrix[3][3] =
	{ pow(x_axis[0],2) * (1 - cos(angle)) + cos(angle),x_axis[0] * x_axis[1] * (1 - cos(angle)) + x_axis[2] * sin(angle),x_axis[0] * x_axis[2] * (1 - cos(angle)) - x_axis[1] * sin(angle),

	 x_axis[0] * x_axis[1] * (1 - cos(angle)) - x_axis[2] * sin(angle),pow(x_axis[1],2) * (1 - cos(angle)) + cos(angle),x_axis[1] * x_axis[2] * (1 - cos(angle)) + x_axis[0] * sin(angle),

	 x_axis[0] * x_axis[2] * (1 - cos(angle)) + x_axis[1] * sin(angle),x_axis[1] * x_axis[2] * (1 - cos(angle)) - x_axis[0] * sin(angle), pow(x_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_dir_vector[3] = { rotateMatrix[0][0] * y_axis[0] + rotateMatrix[0][1] * y_axis[1] + rotateMatrix[0][2] * y_axis[2],
								 rotateMatrix[1][0] * y_axis[0] + rotateMatrix[1][1] * y_axis[1] + rotateMatrix[1][2] * y_axis[2],
								 rotateMatrix[2][0] * y_axis[0] + rotateMatrix[2][1] * y_axis[1] + rotateMatrix[2][2] * y_axis[2] };

	double new_point4[3] = { this->m_style->point->getPoint(1)[0] + new_dir_vector[0],
							 this->m_style->point->getPoint(1)[1] + new_dir_vector[1],
							 this->m_style->point->getPoint(1)[2] + new_dir_vector[2] };

	double new_point6[3] = { this->m_style->point->getPoint(1)[0] - new_dir_vector[0] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[0],
							 this->m_style->point->getPoint(1)[1] - new_dir_vector[1] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[1],
							 this->m_style->point->getPoint(1)[2] - new_dir_vector[2] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[2] };

	double new_point7[3] = { this->m_style->point->getPoint(1)[0] + new_dir_vector[0] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[0],
							 this->m_style->point->getPoint(1)[1] + new_dir_vector[1] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[1],
							 this->m_style->point->getPoint(1)[2] + new_dir_vector[2] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[2] };

	this->m_style->point->changePoint(4, new_point4);
	this->m_style->point->changePoint(6, new_point6);
	this->m_style->point->changePoint(7, new_point7);

	this->operate_window->update();
}

void ProjectMainWindow::l_r_syn()
{
	if (this->m_style->pointNum > 7 || this->m_style->finish)
	{
		this->l_r_box->setValue(this->l_r_scrollbar->value());
		return;
	}
	else if (this->m_style->pointNum < 7)
	{
		this->l_r_scrollbar->setValue(0);
		this->l_r_box->setValue(0);
		return;
	}

	double angle = double(this->l_r_box->value()) - double(this->l_r_scrollbar->value());
	this->l_r_scrollbar->setValue(this->l_r_box->value());

	if (angle == 0)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);


	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);


	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };


	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double* origin = this->m_style->base_actor->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};

	this->m_style->plane_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone1->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone2->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->RotateWXYZ(angle, y_axis[0], y_axis[1], y_axis[2]);
	this->m_style->plane_actor->RotateWXYZ(angle, y_axis[0], y_axis[1], y_axis[2]);
	this->m_style->actor_cone1->RotateWXYZ(angle, y_axis[0], y_axis[1], y_axis[2]);
	this->m_style->actor_cone2->RotateWXYZ(angle, y_axis[0], y_axis[1], y_axis[2]);
	this->m_style->base_actor->SetOrigin(origin);
	this->m_style->plane_actor->SetOrigin(origin);
	this->m_style->actor_cone1->SetOrigin(origin);
	this->m_style->actor_cone2->SetOrigin(origin);


	angle = -angle * acos(-1) / 180;
	double rotateMatrix[3][3] =
	{ pow(y_axis[0],2) * (1 - cos(angle)) + cos(angle),y_axis[0] * y_axis[1] * (1 - cos(angle)) + y_axis[2] * sin(angle),y_axis[0] * y_axis[2] * (1 - cos(angle)) - y_axis[1] * sin(angle),

	 y_axis[0] * y_axis[1] * (1 - cos(angle)) - y_axis[2] * sin(angle),pow(y_axis[1],2) * (1 - cos(angle)) + cos(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) + y_axis[0] * sin(angle),

	 y_axis[0] * y_axis[2] * (1 - cos(angle)) + y_axis[1] * sin(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) - y_axis[0] * sin(angle), pow(y_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	this->m_style->planeNormal[0] = rotateMatrix[0][0] * x_axis[0] + rotateMatrix[0][1] * x_axis[1] + rotateMatrix[0][2] * x_axis[2];
	this->m_style->planeNormal[1] = rotateMatrix[1][0] * x_axis[0] + rotateMatrix[1][1] * x_axis[1] + rotateMatrix[1][2] * x_axis[2];
	this->m_style->planeNormal[2] = rotateMatrix[2][0] * x_axis[0] + rotateMatrix[2][1] * x_axis[1] + rotateMatrix[2][2] * x_axis[2];


	this->operate_window->update();

}

void ProjectMainWindow::u_d_syn()
{
	if (this->m_style->pointNum > 7 || this->m_style->finish)
	{
		this->u_d_box->setValue(this->u_d_scrollbar->value());
		return;
	}
	else if (this->m_style->pointNum < 7)
	{
		this->u_d_scrollbar->setValue(0);
		this->u_d_box->setValue(0);
		return;
	}


	double angle = double(this->u_d_box->value()) - double(this->u_d_scrollbar->value());
	this->u_d_scrollbar->setValue(this->u_d_box->value());

	if (angle == 0)
		return;



	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);


	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);


	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };


	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double* origin = this->m_style->base_actor->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};

	this->m_style->plane_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone1->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone2->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->RotateWXYZ(angle, z_axis[0], z_axis[1], z_axis[2]);
	this->m_style->plane_actor->RotateWXYZ(angle, z_axis[0], z_axis[1], z_axis[2]);
	this->m_style->actor_cone1->RotateWXYZ(angle, z_axis[0], z_axis[1], z_axis[2]);
	this->m_style->actor_cone2->RotateWXYZ(angle, z_axis[0], z_axis[1], z_axis[2]);
	this->m_style->base_actor->SetOrigin(origin);
	this->m_style->plane_actor->SetOrigin(origin);
	this->m_style->actor_cone1->SetOrigin(origin);
	this->m_style->actor_cone2->SetOrigin(origin);



	angle = -angle * acos(-1) / 180;
	double rotateMatrix[3][3] =
	{ pow(z_axis[0],2) * (1 - cos(angle)) + cos(angle),z_axis[0] * z_axis[1] * (1 - cos(angle)) + z_axis[2] * sin(angle),z_axis[0] * z_axis[2] * (1 - cos(angle)) - z_axis[1] * sin(angle),

	 z_axis[0] * z_axis[1] * (1 - cos(angle)) - z_axis[2] * sin(angle),pow(z_axis[1],2) * (1 - cos(angle)) + cos(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) + z_axis[0] * sin(angle),

	 z_axis[0] * z_axis[2] * (1 - cos(angle)) + z_axis[1] * sin(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) - z_axis[0] * sin(angle), pow(z_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	this->m_style->planeNormal[0] = rotateMatrix[0][0] * x_axis[0] + rotateMatrix[0][1] * x_axis[1] + rotateMatrix[0][2] * x_axis[2];
	this->m_style->planeNormal[1] = rotateMatrix[1][0] * x_axis[0] + rotateMatrix[1][1] * x_axis[1] + rotateMatrix[1][2] * x_axis[2];
	this->m_style->planeNormal[2] = rotateMatrix[2][0] * x_axis[0] + rotateMatrix[2][1] * x_axis[1] + rotateMatrix[2][2] * x_axis[2];

	double new_dir_vector[3] = { rotateMatrix[0][0] * y_axis[0] + rotateMatrix[0][1] * y_axis[1] + rotateMatrix[0][2] * y_axis[2],
								 rotateMatrix[1][0] * y_axis[0] + rotateMatrix[1][1] * y_axis[1] + rotateMatrix[1][2] * y_axis[2],
								 rotateMatrix[2][0] * y_axis[0] + rotateMatrix[2][1] * y_axis[1] + rotateMatrix[2][2] * y_axis[2] };

	double new_point4[3] = { this->m_style->point->getPoint(1)[0] + new_dir_vector[0],
							 this->m_style->point->getPoint(1)[1] + new_dir_vector[1],
							 this->m_style->point->getPoint(1)[2] + new_dir_vector[2] };

	double new_point6[3] = { this->m_style->point->getPoint(1)[0] - new_dir_vector[0] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[0],
							 this->m_style->point->getPoint(1)[1] - new_dir_vector[1] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[1],
							 this->m_style->point->getPoint(1)[2] - new_dir_vector[2] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[2] };

	double new_point7[3] = { this->m_style->point->getPoint(1)[0] + new_dir_vector[0] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[0],
							 this->m_style->point->getPoint(1)[1] + new_dir_vector[1] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[1],
							 this->m_style->point->getPoint(1)[2] + new_dir_vector[2] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[2] };

	this->m_style->point->changePoint(4, new_point4);
	this->m_style->point->changePoint(6, new_point6);
	this->m_style->point->changePoint(7, new_point7);


	this->operate_window->update();
}

void ProjectMainWindow::spin_syn()
{

	if (this->m_style->pointNum > 7 || this->m_style->finish)
	{
		this->spin_box->setValue(this->spin_scrollbar->value());
		return;
	}
	else if (this->m_style->pointNum < 7)
	{
		this->spin_scrollbar->setValue(0);
		this->spin_box->setValue(0);
		return;
	}

	double angle = double(this->spin_box->value()) - double(this->spin_scrollbar->value());
	this->spin_scrollbar->setValue(this->spin_box->value());

	if (angle == 0)
		return;

	double* origin = this->m_style->base_actor->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};

	this->m_style->base_actor->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone1->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->actor_cone2->SetOrigin(this->m_style->spin_reference_point);
	this->m_style->base_actor->RotateWXYZ(angle, this->m_style->planeNormal[0], this->m_style->planeNormal[1], this->m_style->planeNormal[2]);
	this->m_style->actor_cone1->RotateWXYZ(angle, this->m_style->planeNormal[0], this->m_style->planeNormal[1], this->m_style->planeNormal[2]);
	this->m_style->actor_cone2->RotateWXYZ(angle, this->m_style->planeNormal[0], this->m_style->planeNormal[1], this->m_style->planeNormal[2]);
	this->m_style->base_actor->SetOrigin(origin);// [0] , origin[1], origin[2]);
	this->m_style->actor_cone1->SetOrigin(origin);
	this->m_style->actor_cone2->SetOrigin(origin);

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);


	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);


	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };


	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	angle = -angle * acos(-1) / 180;

	double rotateMatrix[3][3] =
	{ pow(x_axis[0],2) * (1 - cos(angle)) + cos(angle),x_axis[0] * x_axis[1] * (1 - cos(angle)) + x_axis[2] * sin(angle),x_axis[0] * x_axis[2] * (1 - cos(angle)) - x_axis[1] * sin(angle),

	 x_axis[0] * x_axis[1] * (1 - cos(angle)) - x_axis[2] * sin(angle),pow(x_axis[1],2) * (1 - cos(angle)) + cos(angle),x_axis[1] * x_axis[2] * (1 - cos(angle)) + x_axis[0] * sin(angle),

	 x_axis[0] * x_axis[2] * (1 - cos(angle)) + x_axis[1] * sin(angle),x_axis[1] * x_axis[2] * (1 - cos(angle)) - x_axis[0] * sin(angle), pow(x_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_dir_vector[3] = { rotateMatrix[0][0] * y_axis[0] + rotateMatrix[0][1] * y_axis[1] + rotateMatrix[0][2] * y_axis[2],
								 rotateMatrix[1][0] * y_axis[0] + rotateMatrix[1][1] * y_axis[1] + rotateMatrix[1][2] * y_axis[2],
								 rotateMatrix[2][0] * y_axis[0] + rotateMatrix[2][1] * y_axis[1] + rotateMatrix[2][2] * y_axis[2] };

	double new_point4[3] = { this->m_style->point->getPoint(1)[0] + new_dir_vector[0],
							 this->m_style->point->getPoint(1)[1] + new_dir_vector[1],
							 this->m_style->point->getPoint(1)[2] + new_dir_vector[2] };

	double new_point6[3] = { this->m_style->point->getPoint(1)[0] - new_dir_vector[0] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[0],
							 this->m_style->point->getPoint(1)[1] - new_dir_vector[1] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[1],
							 this->m_style->point->getPoint(1)[2] - new_dir_vector[2] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[2] };

	double new_point7[3] = { this->m_style->point->getPoint(1)[0] + new_dir_vector[0] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[0],
							 this->m_style->point->getPoint(1)[1] + new_dir_vector[1] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[1],
							 this->m_style->point->getPoint(1)[2] + new_dir_vector[2] * this->m_style->distance / 2 - this->m_style->screw_apex_offset * this->m_style->planeNormal[2] };

	this->m_style->point->changePoint(4, new_point4);
	this->m_style->point->changePoint(6, new_point6);
	this->m_style->point->changePoint(7, new_point7);

	this->operate_window->update();
}




void ProjectMainWindow::change_iso_value()
{
	////this->m_style->boneExtractor->SetInputData(this->m_style->boneIMGData);
	//this->m_style->boneExtractor->SetValue(0, this->marchingCubes_sb->value());
	////this->m_style->boneExtractor->ComputeNormalsOn();
	//this->m_style->boneExtractor->Update();
	////this->m_style->boneExtractor->Modified();
	//this->operate_window->update();
	return;
}


void ProjectMainWindow::up_revision1()
{
	if (!this->m_style->finish)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);

	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);

	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double path1[3] = { this->m_style->finalPath[3] - this->m_style->finalPath[0],
						this->m_style->finalPath[4] - this->m_style->finalPath[1],
						this->m_style->finalPath[5] - this->m_style->finalPath[2] };
	double angle = acos(-1) / 180;

	double rotateMatrix[3][3] =
	{ pow(z_axis[0],2) * (1 - cos(angle)) + cos(angle),z_axis[0] * z_axis[1] * (1 - cos(angle)) + z_axis[2] * sin(angle),z_axis[0] * z_axis[2] * (1 - cos(angle)) - z_axis[1] * sin(angle),

	 z_axis[0] * z_axis[1] * (1 - cos(angle)) - z_axis[2] * sin(angle),pow(z_axis[1],2) * (1 - cos(angle)) + cos(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) + z_axis[0] * sin(angle),

	 z_axis[0] * z_axis[2] * (1 - cos(angle)) + z_axis[1] * sin(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) - z_axis[0] * sin(angle), pow(z_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_path1[3] = { rotateMatrix[0][0] * path1[0] + rotateMatrix[0][1] * path1[1] + rotateMatrix[0][2] * path1[2],
							rotateMatrix[1][0] * path1[0] + rotateMatrix[1][1] * path1[1] + rotateMatrix[1][2] * path1[2],
							rotateMatrix[2][0] * path1[0] + rotateMatrix[2][1] * path1[1] + rotateMatrix[2][2] * path1[2] };

	double angle_with_middle = acos((new_path1[0] * this->m_style->planeNormal[0] + new_path1[1] * this->m_style->planeNormal[1] + new_path1[2] * this->m_style->planeNormal[2]) / vtkMath::Norm(new_path1));

	if (angle_with_middle * 180 / acos(-1) >= 15)
	{
		QMessageBox::warning(this, tr("warning"), tr("The angle between this screw and the middle peg exceeds 15 degree!"));
		return;
	}
	double intersect_ornot = new_path1[0] * dir_vectors[0] + new_path1[1] * dir_vectors[1] + new_path1[2] * dir_vectors[2];

	if (intersect_ornot > 0)
	{
		QMessageBox::warning(this, tr("warning"), tr("There may be interference  between the screw and the middle peg !"));
		return;
	}

	//double* origin = this->m_style->screw_actor1->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};	
	this->m_style->screw_actor1->SetOrigin(this->m_style->point->getPoint(6));
	this->m_style->screw_actor1->RotateWXYZ(-1, z_axis[0], z_axis[1], z_axis[2]);
	this->m_style->screw_actor1->SetOrigin(this->m_style->spin_reference_point);

	double new_end_point1[3] = { this->m_style->finalPath[0] + new_path1[0],
								 this->m_style->finalPath[1] + new_path1[1],
								 this->m_style->finalPath[2] + new_path1[2] };
	this->m_style->finalPath[3] = new_end_point1[0];
	this->m_style->finalPath[4] = new_end_point1[1];
	this->m_style->finalPath[5] = new_end_point1[2];

	vtkSmartPointer<vtkTransform> screw_transform1 =
		vtkSmartPointer<vtkTransform>::New();
	screw_transform1->PostMultiply();
	screw_transform1->Translate(-this->m_style->finalPath[0], -this->m_style->finalPath[1], - this->m_style->finalPath[2]);
	/*double screw1_matrix[16] = { 0 };
	for (int i = 0;i < 3;i++)
	{
		screw1_matrix[i * 4 + 3] = this->m_style->finalPath[i];
		for (int j = 0;j < 3;j++)
		{
			screw1_matrix[i * 4 + j] = rotateMatrix[i][j];
		}
	}
	screw1_matrix[15] = 1;
	screw_transform1->SetMatrix(screw1_matrix);*/
	screw_transform1->RotateWXYZ(-1, z_axis[0], z_axis[1], z_axis[2]);
	screw_transform1->Translate(this->m_style->finalPath[0], this->m_style->finalPath[1], this->m_style->finalPath[2]);
	screw_transform1->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> screw1_transformPD =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	screw1_transformPD->SetTransform(screw_transform1);
	screw1_transformPD->SetInputData(this->m_style->screw1_poly_data);
	screw1_transformPD->Update();

	this->m_style->screw1_poly_data = screw1_transformPD->GetOutput();

	this->m_style->callback1->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_1->setEnabled(1);

	this->m_style->callback2->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_2->setEnabled(1);

	this->m_style->callback3->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_3->setEnabled(1);

	this->qvtkWidget_1->GetRenderWindow()->Render();
	this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
	this->qvtkWidget_1->update();

	this->qvtkWidget_2->GetRenderWindow()->Render();
	this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
	this->qvtkWidget_2->update();

	this->qvtkWidget_3->GetRenderWindow()->Render();
	this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
	this->qvtkWidget_3->update();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}


	//验证坐标是否正确
	/*vtkSmartPointer<vtkSphereSource> sphere =
		vtkSmartPointer<vtkSphereSource>::New();
	sphere->SetCenter(new_end_point1);
	sphere->SetRadius(15);
	sphere->Update();

	vtkSmartPointer<vtkPolyDataMapper> testMapper3 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	testMapper3->SetInputData(sphere->GetOutput());

	vtkSmartPointer<vtkActor> testActor3 =
		vtkSmartPointer<vtkActor>::New();
	testActor3->SetMapper(testMapper3);
	testActor3->GetProperty()->SetColor(1, 0, 0);
	testActor3->GetProperty()->SetOpacity(1);
	this->m_pRenderer->AddActor(testActor3);*/

	this->operate_window->update();
}

void ProjectMainWindow::down_revision1()
{
	if (!this->m_style->finish)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);

	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);

	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double path1[3] = { this->m_style->finalPath[3] - this->m_style->finalPath[0],
						this->m_style->finalPath[4] - this->m_style->finalPath[1],
						this->m_style->finalPath[5] - this->m_style->finalPath[2] };
	double angle = -acos(-1) / 180;

	double rotateMatrix[3][3] =
	{ pow(z_axis[0],2) * (1 - cos(angle)) + cos(angle),z_axis[0] * z_axis[1] * (1 - cos(angle)) + z_axis[2] * sin(angle),z_axis[0] * z_axis[2] * (1 - cos(angle)) - z_axis[1] * sin(angle),

	 z_axis[0] * z_axis[1] * (1 - cos(angle)) - z_axis[2] * sin(angle),pow(z_axis[1],2) * (1 - cos(angle)) + cos(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) + z_axis[0] * sin(angle),

	 z_axis[0] * z_axis[2] * (1 - cos(angle)) + z_axis[1] * sin(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) - z_axis[0] * sin(angle), pow(z_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_path1[3] = { rotateMatrix[0][0] * path1[0] + rotateMatrix[0][1] * path1[1] + rotateMatrix[0][2] * path1[2],
							rotateMatrix[1][0] * path1[0] + rotateMatrix[1][1] * path1[1] + rotateMatrix[1][2] * path1[2],
							rotateMatrix[2][0] * path1[0] + rotateMatrix[2][1] * path1[1] + rotateMatrix[2][2] * path1[2] };

	double angle_with_middle = acos((new_path1[0] * this->m_style->planeNormal[0] + new_path1[1] * this->m_style->planeNormal[1] + new_path1[2] * this->m_style->planeNormal[2]) / vtkMath::Norm(new_path1));
	if (angle_with_middle * 180 / acos(-1) >= 15)
	{
		QMessageBox::warning(this, tr("warning"), tr("The angle between this screw and the middle peg exceeds 15 degree!"));
		return;
	}

	double intersect_ornot = new_path1[0] * dir_vectors[0] + new_path1[1] * dir_vectors[1] + new_path1[2] * dir_vectors[2];
	if (intersect_ornot > 0)
	{
		QMessageBox::warning(this, tr("warning"), tr("There may be interference  between the screw and the middle peg !"));
		return;
	}


	//double* origin = this->m_style->screw_actor1->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};	
	this->m_style->screw_actor1->SetOrigin(this->m_style->point->getPoint(6));
	this->m_style->screw_actor1->RotateWXYZ(1, z_axis[0], z_axis[1], z_axis[2]);
	vtkSmartPointer<vtkMatrix4x4> actor_matrix =  this->m_style->screw_actor1->GetMatrix();
	//this->m_style->screw_actor1->SetOrigin(this->m_style->spin_reference_point);

	double new_end_point1[3] = { this->m_style->finalPath[0] + new_path1[0],
								 this->m_style->finalPath[1] + new_path1[1],
								 this->m_style->finalPath[2] + new_path1[2] };
	this->m_style->finalPath[3] = new_end_point1[0];
	this->m_style->finalPath[4] = new_end_point1[1];
	this->m_style->finalPath[5] = new_end_point1[2];

	vtkSmartPointer<vtkTransform> screw_transform1 =
		vtkSmartPointer<vtkTransform>::New();
	screw_transform1->PostMultiply();
	screw_transform1->Translate(-this->m_style->finalPath[0], -this->m_style->finalPath[1], -this->m_style->finalPath[2]);
	/*double screw1_matrix[16] = { 0 };
	for (int i = 0;i < 3;i++)
	{
		screw1_matrix[i * 4 + 3] = this->m_style->finalPath[i];
		for (int j = 0;j < 3;j++)
		{
			screw1_matrix[i * 4 + j] = rotateMatrix[i][j];
		}
	}
	screw1_matrix[15] = 1;
	screw_transform1->SetMatrix(screw1_matrix);*/
	screw_transform1->RotateWXYZ(1, z_axis[0], z_axis[1], z_axis[2]);
	screw_transform1->Translate(this->m_style->finalPath[0], this->m_style->finalPath[1], this->m_style->finalPath[2]);
	screw_transform1->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> screw1_transformPD =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	screw1_transformPD->SetTransform(screw_transform1);
	screw1_transformPD->SetInputData(this->m_style->screw1_poly_data);
	screw1_transformPD->Update();

	this->m_style->screw1_poly_data = screw1_transformPD->GetOutput();

	this->m_style->callback1->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_1->setEnabled(1);

	this->m_style->callback2->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_2->setEnabled(1);

	this->m_style->callback3->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_3->setEnabled(1);

	this->qvtkWidget_1->GetRenderWindow()->Render();
	this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
	this->qvtkWidget_1->update();

	this->qvtkWidget_2->GetRenderWindow()->Render();
	this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
	this->qvtkWidget_2->update();

	this->qvtkWidget_3->GetRenderWindow()->Render();
	this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
	this->qvtkWidget_3->update();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}

	//验证坐标是否正确
	/*vtkSmartPointer<vtkSphereSource> sphere =
		vtkSmartPointer<vtkSphereSource>::New();
	sphere->SetCenter(new_end_point1);
	sphere->SetRadius(5);
	sphere->Update();

	vtkSmartPointer<vtkPolyDataMapper> testMapper3 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	testMapper3->SetInputData(sphere->GetOutput());

	vtkSmartPointer<vtkActor> testActor3 =
		vtkSmartPointer<vtkActor>::New();
	testActor3->SetMapper(testMapper3);
	testActor3->GetProperty()->SetColor(1, 0, 0);
	testActor3->GetProperty()->SetOpacity(1);
	this->m_pRenderer->AddActor(testActor3);*/

	this->operate_window->update();
}

void ProjectMainWindow::left_revision1()
{
	if (!this->m_style->finish)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);

	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);

	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double path1[3] = { this->m_style->finalPath[3] - this->m_style->finalPath[0],
						this->m_style->finalPath[4] - this->m_style->finalPath[1],
						this->m_style->finalPath[5] - this->m_style->finalPath[2] };
	double angle = acos(-1) / 180;

	double rotateMatrix[3][3] =
	{ pow(y_axis[0],2) * (1 - cos(angle)) + cos(angle),y_axis[0] * y_axis[1] * (1 - cos(angle)) + y_axis[2] * sin(angle),y_axis[0] * y_axis[2] * (1 - cos(angle)) - y_axis[1] * sin(angle),

	 y_axis[0] * y_axis[1] * (1 - cos(angle)) - y_axis[2] * sin(angle),pow(y_axis[1],2) * (1 - cos(angle)) + cos(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) + y_axis[0] * sin(angle),

	 y_axis[0] * y_axis[2] * (1 - cos(angle)) + y_axis[1] * sin(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) - y_axis[0] * sin(angle), pow(y_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_path1[3] = { rotateMatrix[0][0] * path1[0] + rotateMatrix[0][1] * path1[1] + rotateMatrix[0][2] * path1[2],
							rotateMatrix[1][0] * path1[0] + rotateMatrix[1][1] * path1[1] + rotateMatrix[1][2] * path1[2],
							rotateMatrix[2][0] * path1[0] + rotateMatrix[2][1] * path1[1] + rotateMatrix[2][2] * path1[2] };

	double angle_with_middle = acos((new_path1[0] * this->m_style->planeNormal[0] + new_path1[1] * this->m_style->planeNormal[1] + new_path1[2] * this->m_style->planeNormal[2]) / vtkMath::Norm(new_path1));
	if (angle_with_middle * 180 / acos(-1) >= 15)
	{
		QMessageBox::warning(this, tr("warning"), tr("The angle between this screw and the middle peg exceeds 15 degree!"));
		return;
	}

	double intersect_ornot = new_path1[0] * dir_vectors[0] + new_path1[1] * dir_vectors[1] + new_path1[2] * dir_vectors[2];
	if (intersect_ornot > 0)
	{
		QMessageBox::warning(this, tr("warning"), tr("There may be interference  between the screw and the middle peg !"));
		return;
	}


	//double* origin = this->m_style->screw_actor1->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};	
	this->m_style->screw_actor1->SetOrigin(this->m_style->point->getPoint(6));
	this->m_style->screw_actor1->RotateWXYZ(-1, y_axis[0], y_axis[1], y_axis[2]);
	//this->m_style->screw_actor1->SetOrigin(this->m_style->spin_reference_point);

	double new_end_point1[3] = { this->m_style->finalPath[0] + new_path1[0],
								 this->m_style->finalPath[1] + new_path1[1],
								 this->m_style->finalPath[2] + new_path1[2] };
	this->m_style->finalPath[3] = new_end_point1[0];
	this->m_style->finalPath[4] = new_end_point1[1];
	this->m_style->finalPath[5] = new_end_point1[2];

	vtkSmartPointer<vtkTransform> screw_transform1 =
		vtkSmartPointer<vtkTransform>::New();
	screw_transform1->PostMultiply();
	screw_transform1->Translate(-this->m_style->finalPath[0], -this->m_style->finalPath[1], -this->m_style->finalPath[2]);
	/*double screw1_matrix[16] = { 0 };
	for (int i = 0;i < 3;i++)
	{
		screw1_matrix[i * 4 + 3] = this->m_style->finalPath[i];
		for (int j = 0;j < 3;j++)
		{
			screw1_matrix[i * 4 + j] = rotateMatrix[i][j];
		}
	}
	screw1_matrix[15] = 1;
	screw_transform1->SetMatrix(screw1_matrix);*/
	screw_transform1->RotateWXYZ(-1, y_axis[0], y_axis[1], y_axis[2]);
	screw_transform1->Translate(this->m_style->finalPath[0], this->m_style->finalPath[1], this->m_style->finalPath[2]);
	screw_transform1->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> screw1_transformPD =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	screw1_transformPD->SetTransform(screw_transform1);
	screw1_transformPD->SetInputData(this->m_style->screw1_poly_data);
	screw1_transformPD->Update();

	this->m_style->screw1_poly_data = screw1_transformPD->GetOutput();

	this->m_style->callback1->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_1->setEnabled(1);

	this->m_style->callback2->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_2->setEnabled(1);

	this->m_style->callback3->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_3->setEnabled(1);

	this->qvtkWidget_1->GetRenderWindow()->Render();
	this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
	this->qvtkWidget_1->update();

	this->qvtkWidget_2->GetRenderWindow()->Render();
	this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
	this->qvtkWidget_2->update();

	this->qvtkWidget_3->GetRenderWindow()->Render();
	this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
	this->qvtkWidget_3->update();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}

	//验证坐标是否正确
	/*vtkSmartPointer<vtkSphereSource> sphere =
		vtkSmartPointer<vtkSphereSource>::New();
	sphere->SetCenter(new_end_point1);
	sphere->SetRadius(5);
	sphere->Update();

	vtkSmartPointer<vtkPolyDataMapper> testMapper3 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	testMapper3->SetInputData(sphere->GetOutput());

	vtkSmartPointer<vtkActor> testActor3 =
		vtkSmartPointer<vtkActor>::New();
	testActor3->SetMapper(testMapper3);
	testActor3->GetProperty()->SetColor(1, 0, 0);
	testActor3->GetProperty()->SetOpacity(1);
	this->m_pRenderer->AddActor(testActor3);*/

	this->operate_window->update();
}

void ProjectMainWindow::right_revision1()
{
	if (!this->m_style->finish)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);

	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);

	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double path1[3] = { this->m_style->finalPath[3] - this->m_style->finalPath[0],
						this->m_style->finalPath[4] - this->m_style->finalPath[1],
						this->m_style->finalPath[5] - this->m_style->finalPath[2] };
	double angle = -acos(-1) / 180;

	double rotateMatrix[3][3] =
	{ pow(y_axis[0],2) * (1 - cos(angle)) + cos(angle),y_axis[0] * y_axis[1] * (1 - cos(angle)) + y_axis[2] * sin(angle),y_axis[0] * y_axis[2] * (1 - cos(angle)) - y_axis[1] * sin(angle),

	 y_axis[0] * y_axis[1] * (1 - cos(angle)) - y_axis[2] * sin(angle),pow(y_axis[1],2) * (1 - cos(angle)) + cos(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) + y_axis[0] * sin(angle),

	 y_axis[0] * y_axis[2] * (1 - cos(angle)) + y_axis[1] * sin(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) - y_axis[0] * sin(angle), pow(y_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_path1[3] = { rotateMatrix[0][0] * path1[0] + rotateMatrix[0][1] * path1[1] + rotateMatrix[0][2] * path1[2],
							rotateMatrix[1][0] * path1[0] + rotateMatrix[1][1] * path1[1] + rotateMatrix[1][2] * path1[2],
							rotateMatrix[2][0] * path1[0] + rotateMatrix[2][1] * path1[1] + rotateMatrix[2][2] * path1[2] };

	double angle_with_middle = acos((new_path1[0] * this->m_style->planeNormal[0] + new_path1[1] * this->m_style->planeNormal[1] + new_path1[2] * this->m_style->planeNormal[2]) / vtkMath::Norm(new_path1));
	if (angle_with_middle * 180 / acos(-1) >= 15)
	{
		QMessageBox::warning(this, tr("warning"), tr("The angle between this screw and the middle peg exceeds 15 degree!"));
		return;
	}

	double intersect_ornot = new_path1[0] * dir_vectors[0] + new_path1[1] * dir_vectors[1] + new_path1[2] * dir_vectors[2];
	if (intersect_ornot > 0)
	{
		QMessageBox::warning(this, tr("warning"), tr("There may be interference  between the screw and the middle peg !"));
		return;
	}


	//double* origin = this->m_style->screw_actor1->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};	
	this->m_style->screw_actor1->SetOrigin(this->m_style->point->getPoint(6));
	this->m_style->screw_actor1->RotateWXYZ(1, y_axis[0], y_axis[1], y_axis[2]);
	//this->m_style->screw_actor1->SetOrigin(this->m_style->spin_reference_point);

	double new_end_point1[3] = { this->m_style->finalPath[0] + new_path1[0],
								 this->m_style->finalPath[1] + new_path1[1],
								 this->m_style->finalPath[2] + new_path1[2] };
	this->m_style->finalPath[3] = new_end_point1[0];
	this->m_style->finalPath[4] = new_end_point1[1];
	this->m_style->finalPath[5] = new_end_point1[2];

	vtkSmartPointer<vtkTransform> screw_transform1 =
		vtkSmartPointer<vtkTransform>::New();
	screw_transform1->PostMultiply();
	screw_transform1->Translate(-this->m_style->finalPath[0], -this->m_style->finalPath[1], -this->m_style->finalPath[2]);
	/*double screw1_matrix[16] = { 0 };
	for (int i = 0;i < 3;i++)
	{
		screw1_matrix[i * 4 + 3] = this->m_style->finalPath[i];
		for (int j = 0;j < 3;j++)
		{
			screw1_matrix[i * 4 + j] = rotateMatrix[i][j];
		}
	}
	screw1_matrix[15] = 1;
	screw_transform1->SetMatrix(screw1_matrix);*/
	screw_transform1->RotateWXYZ(1, y_axis[0], y_axis[1], y_axis[2]);
	screw_transform1->Translate(this->m_style->finalPath[0], this->m_style->finalPath[1], this->m_style->finalPath[2]);
	screw_transform1->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> screw1_transformPD =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	screw1_transformPD->SetTransform(screw_transform1);
	screw1_transformPD->SetInputData(this->m_style->screw1_poly_data);
	screw1_transformPD->Update();

	this->m_style->screw1_poly_data = screw1_transformPD->GetOutput();

	this->m_style->callback1->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_1->setEnabled(1);

	this->m_style->callback2->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_2->setEnabled(1);

	this->m_style->callback3->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_3->setEnabled(1);

	this->qvtkWidget_1->GetRenderWindow()->Render();
	this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
	this->qvtkWidget_1->update();

	this->qvtkWidget_2->GetRenderWindow()->Render();
	this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
	this->qvtkWidget_2->update();

	this->qvtkWidget_3->GetRenderWindow()->Render();
	this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
	this->qvtkWidget_3->update();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}

	//验证坐标是否正确
	/*vtkSmartPointer<vtkSphereSource> sphere =
		vtkSmartPointer<vtkSphereSource>::New();
	sphere->SetCenter(new_end_point1);
	sphere->SetRadius(5);
	sphere->Update();

	vtkSmartPointer<vtkPolyDataMapper> testMapper3 =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	testMapper3->SetInputData(sphere->GetOutput());

	vtkSmartPointer<vtkActor> testActor3 =
		vtkSmartPointer<vtkActor>::New();
	testActor3->SetMapper(testMapper3);
	testActor3->GetProperty()->SetColor(1, 0, 0);
	testActor3->GetProperty()->SetOpacity(1);
	this->m_pRenderer->AddActor(testActor3);*/

	this->operate_window->update();
}


void ProjectMainWindow::up_revision2()
{
	if (!this->m_style->finish)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);

	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);

	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double path3[3] = { this->m_style->finalPath[15] - this->m_style->finalPath[12],
						this->m_style->finalPath[16] - this->m_style->finalPath[13],
						this->m_style->finalPath[17] - this->m_style->finalPath[14] };
	double angle = acos(-1) / 180;

	double rotateMatrix[3][3] =
	{ pow(z_axis[0],2) * (1 - cos(angle)) + cos(angle),z_axis[0] * z_axis[1] * (1 - cos(angle)) + z_axis[2] * sin(angle),z_axis[0] * z_axis[2] * (1 - cos(angle)) - z_axis[1] * sin(angle),

	 z_axis[0] * z_axis[1] * (1 - cos(angle)) - z_axis[2] * sin(angle),pow(z_axis[1],2) * (1 - cos(angle)) + cos(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) + z_axis[0] * sin(angle),

	 z_axis[0] * z_axis[2] * (1 - cos(angle)) + z_axis[1] * sin(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) - z_axis[0] * sin(angle), pow(z_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_path3[3] = { rotateMatrix[0][0] * path3[0] + rotateMatrix[0][1] * path3[1] + rotateMatrix[0][2] * path3[2],
							rotateMatrix[1][0] * path3[0] + rotateMatrix[1][1] * path3[1] + rotateMatrix[1][2] * path3[2],
							rotateMatrix[2][0] * path3[0] + rotateMatrix[2][1] * path3[1] + rotateMatrix[2][2] * path3[2] };

	double angle_with_middle = acos((new_path3[0] * this->m_style->planeNormal[0] + new_path3[1] * this->m_style->planeNormal[1] + new_path3[2] * this->m_style->planeNormal[2]) / vtkMath::Norm(new_path3));

	if (angle_with_middle * 180 / acos(-1) >= 15)
	{
		QMessageBox::warning(this, tr("warning"), tr("The angle between this screw and the middle peg exceeds 15 degree!"));
		return;
	}
	double intersect_ornot = new_path3[0] * dir_vectors[0] + new_path3[1] * dir_vectors[1] + new_path3[2] * dir_vectors[2];

	if (intersect_ornot < 0)
	{
		QMessageBox::warning(this, tr("warning"), tr("There may be interference  between the screw and the middle peg !"));
		return;
	}


	//double* origin = this->m_style->screw_actor1->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};	
	this->m_style->screw_actor2->SetOrigin(this->m_style->point->getPoint(7));
	this->m_style->screw_actor2->RotateWXYZ(-1, z_axis[0], z_axis[1], z_axis[2]);
	//this->m_style->screw_actor2->SetOrigin(this->m_style->spin_reference_point);

	double new_end_point3[3] = { this->m_style->finalPath[12] + new_path3[0],
								 this->m_style->finalPath[13] + new_path3[1],
								 this->m_style->finalPath[14] + new_path3[2] };
	this->m_style->finalPath[15] = new_end_point3[0];
	this->m_style->finalPath[16] = new_end_point3[1];
	this->m_style->finalPath[17] = new_end_point3[2];

	vtkSmartPointer<vtkTransform> screw_transform2 =
		vtkSmartPointer<vtkTransform>::New();
	screw_transform2->PostMultiply();
	screw_transform2->Translate(-this->m_style->finalPath[12], -this->m_style->finalPath[13], -this->m_style->finalPath[14]);
	/*double screw2_matrix[16] = { 0 };
	for (int i = 0;i < 3;i++)
	{
		screw2_matrix[i * 4 + 3] = this->m_style->finalPath[i+12];
		for (int j = 0;j < 3;j++)
		{
			screw2_matrix[i * 4 + j] = rotateMatrix[i][j];
		}
	}
	screw2_matrix[15] = 1;
	screw_transform2->SetMatrix(screw2_matrix);*/
	screw_transform2->RotateWXYZ(-1, z_axis[0],z_axis[1],z_axis[2]);
	screw_transform2->Translate(this->m_style->finalPath[12], this->m_style->finalPath[13], this->m_style->finalPath[14]);
	screw_transform2->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> screw2_transformPD =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	screw2_transformPD->SetTransform(screw_transform2);
	screw2_transformPD->SetInputData(this->m_style->screw2_poly_data);
	screw2_transformPD->Update();

	this->m_style->screw2_poly_data = screw2_transformPD->GetOutput();

	this->m_style->callback1->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_1->setEnabled(1);

	this->m_style->callback2->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_2->setEnabled(1);

	this->m_style->callback3->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_3->setEnabled(1);

	this->qvtkWidget_1->GetRenderWindow()->Render();
	this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
	this->qvtkWidget_1->update();

	this->qvtkWidget_2->GetRenderWindow()->Render();
	this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
	this->qvtkWidget_2->update();

	this->qvtkWidget_3->GetRenderWindow()->Render();
	this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
	this->qvtkWidget_3->update();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}

	this->operate_window->update();
}

void ProjectMainWindow::down_revision2()
{
	if (!this->m_style->finish)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);

	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);

	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double path3[3] = { this->m_style->finalPath[15] - this->m_style->finalPath[12],
						this->m_style->finalPath[16] - this->m_style->finalPath[13],
						this->m_style->finalPath[17] - this->m_style->finalPath[14] };
	double angle = -acos(-1) / 180;

	double rotateMatrix[3][3] =
	{ pow(z_axis[0],2) * (1 - cos(angle)) + cos(angle),z_axis[0] * z_axis[1] * (1 - cos(angle)) + z_axis[2] * sin(angle),z_axis[0] * z_axis[2] * (1 - cos(angle)) - z_axis[1] * sin(angle),

	 z_axis[0] * z_axis[1] * (1 - cos(angle)) - z_axis[2] * sin(angle),pow(z_axis[1],2) * (1 - cos(angle)) + cos(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) + z_axis[0] * sin(angle),

	 z_axis[0] * z_axis[2] * (1 - cos(angle)) + z_axis[1] * sin(angle),z_axis[1] * z_axis[2] * (1 - cos(angle)) - z_axis[0] * sin(angle), pow(z_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_path3[3] = { rotateMatrix[0][0] * path3[0] + rotateMatrix[0][1] * path3[1] + rotateMatrix[0][2] * path3[2],
							rotateMatrix[1][0] * path3[0] + rotateMatrix[1][1] * path3[1] + rotateMatrix[1][2] * path3[2],
							rotateMatrix[2][0] * path3[0] + rotateMatrix[2][1] * path3[1] + rotateMatrix[2][2] * path3[2] };

	double angle_with_middle = acos((new_path3[0] * this->m_style->planeNormal[0] + new_path3[1] * this->m_style->planeNormal[1] + new_path3[2] * this->m_style->planeNormal[2]) / vtkMath::Norm(new_path3));

	if (angle_with_middle * 180 / acos(-1) >= 15)
	{
		QMessageBox::warning(this, tr("warning"), tr("The angle between this screw and the middle peg exceeds 15 degree!"));
		return;
	}
	double intersect_ornot = new_path3[0] * dir_vectors[0] + new_path3[1] * dir_vectors[1] + new_path3[2] * dir_vectors[2];

	if (intersect_ornot < 0)
	{
		QMessageBox::warning(this, tr("warning"), tr("There may be interference  between the screw and the middle peg !"));
		return;
	}


	//double* origin = this->m_style->screw_actor1->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};	
	this->m_style->screw_actor2->SetOrigin(this->m_style->point->getPoint(7));
	this->m_style->screw_actor2->RotateWXYZ(1, z_axis[0], z_axis[1], z_axis[2]);
	//this->m_style->screw_actor2->SetOrigin(this->m_style->spin_reference_point);

	double new_end_point3[3] = { this->m_style->finalPath[12] + new_path3[0],
								 this->m_style->finalPath[13] + new_path3[1],
								 this->m_style->finalPath[14] + new_path3[2] };
	this->m_style->finalPath[15] = new_end_point3[0];
	this->m_style->finalPath[16] = new_end_point3[1];
	this->m_style->finalPath[17] = new_end_point3[2];

	vtkSmartPointer<vtkTransform> screw_transform2 =
		vtkSmartPointer<vtkTransform>::New();
	screw_transform2->PostMultiply();
	/*double screw2_matrix[16] = { 0 };
	for (int i = 0;i < 3;i++)
	{
		screw2_matrix[i * 4 + 3] = this->m_style->finalPath[i + 12];
		for (int j = 0;j < 3;j++)
		{
			screw2_matrix[i * 4 + j] = rotateMatrix[i][j];
		}
	}
	screw2_matrix[15] = 1;
		screw_transform2->Translate(-this->m_style->finalPath[12], -this->m_style->finalPath[13], -this->m_style->finalPath[14]);
screw_transform2->SetMatrix(screw2_matrix);*/
	screw_transform2->RotateWXYZ(1, z_axis[0], z_axis[1], z_axis[2]);
	screw_transform2->Translate(this->m_style->finalPath[12], this->m_style->finalPath[13], this->m_style->finalPath[14]);
	screw_transform2->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> screw2_transformPD =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	screw2_transformPD->SetTransform(screw_transform2);
	screw2_transformPD->SetInputData(this->m_style->screw2_poly_data);
	screw2_transformPD->Update();

	this->m_style->screw2_poly_data = screw2_transformPD->GetOutput();

	this->m_style->callback1->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_1->setEnabled(1);

	this->m_style->callback2->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_2->setEnabled(1);

	this->m_style->callback3->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_3->setEnabled(1);

	this->qvtkWidget_1->GetRenderWindow()->Render();
	this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
	this->qvtkWidget_1->update();

	this->qvtkWidget_2->GetRenderWindow()->Render();
	this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
	this->qvtkWidget_2->update();

	this->qvtkWidget_3->GetRenderWindow()->Render();
	this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
	this->qvtkWidget_3->update();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}
	this->operate_window->update();
}

void ProjectMainWindow::left_revision2()
{
	if (!this->m_style->finish)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);

	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);

	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double path3[3] = { this->m_style->finalPath[15] - this->m_style->finalPath[12],
						this->m_style->finalPath[16] - this->m_style->finalPath[13],
						this->m_style->finalPath[17] - this->m_style->finalPath[14] };
	double angle = acos(-1) / 180;

	double rotateMatrix[3][3] =
	{ pow(y_axis[0],2) * (1 - cos(angle)) + cos(angle),y_axis[0] * y_axis[1] * (1 - cos(angle)) + y_axis[2] * sin(angle),y_axis[0] * y_axis[2] * (1 - cos(angle)) - y_axis[1] * sin(angle),

	 y_axis[0] * y_axis[1] * (1 - cos(angle)) - y_axis[2] * sin(angle),pow(y_axis[1],2) * (1 - cos(angle)) + cos(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) + y_axis[0] * sin(angle),

	 y_axis[0] * y_axis[2] * (1 - cos(angle)) + y_axis[1] * sin(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) - y_axis[0] * sin(angle), pow(y_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_path3[3] = { rotateMatrix[0][0] * path3[0] + rotateMatrix[0][1] * path3[1] + rotateMatrix[0][2] * path3[2],
							rotateMatrix[1][0] * path3[0] + rotateMatrix[1][1] * path3[1] + rotateMatrix[1][2] * path3[2],
							rotateMatrix[2][0] * path3[0] + rotateMatrix[2][1] * path3[1] + rotateMatrix[2][2] * path3[2] };

	double angle_with_middle = acos((new_path3[0] * this->m_style->planeNormal[0] + new_path3[1] * this->m_style->planeNormal[1] + new_path3[2] * this->m_style->planeNormal[2]) / vtkMath::Norm(new_path3));
	if (angle_with_middle * 180 / acos(-1) >= 15)
	{
		QMessageBox::warning(this, tr("warning"), tr("The angle between this screw and the middle peg exceeds 15 degree!"));
		return;
	}

	double intersect_ornot = new_path3[0] * dir_vectors[0] + new_path3[1] * dir_vectors[1] + new_path3[2] * dir_vectors[2];
	if (intersect_ornot < 0)
	{
		QMessageBox::warning(this, tr("warning"), tr("There may be interference  between the screw and the middle peg !"));
		return;
	}


	//double* origin = this->m_style->screw_actor1->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};	
	this->m_style->screw_actor2->SetOrigin(this->m_style->point->getPoint(7));
	this->m_style->screw_actor2->RotateWXYZ(-1, y_axis[0], y_axis[1], y_axis[2]);
	//this->m_style->screw_actor2->SetOrigin(this->m_style->spin_reference_point);
	this->operate_window->update();

	double new_end_point3[3] = { this->m_style->finalPath[12] + new_path3[0],
								 this->m_style->finalPath[13] + new_path3[1],
								 this->m_style->finalPath[14] + new_path3[2] };
	this->m_style->finalPath[15] = new_end_point3[0];
	this->m_style->finalPath[16] = new_end_point3[1];
	this->m_style->finalPath[17] = new_end_point3[2];

	vtkSmartPointer<vtkTransform> screw_transform2 =
		vtkSmartPointer<vtkTransform>::New();
	screw_transform2->PostMultiply();
	screw_transform2->Translate(-this->m_style->finalPath[12], -this->m_style->finalPath[13], -this->m_style->finalPath[14]);
	screw_transform2->RotateWXYZ(-1, y_axis[0], y_axis[1], y_axis[2]);
	screw_transform2->Translate(this->m_style->finalPath[12], this->m_style->finalPath[13], this->m_style->finalPath[14]);
	screw_transform2->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> screw2_transformPD =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	screw2_transformPD->SetTransform(screw_transform2);
	screw2_transformPD->SetInputData(this->m_style->screw2_poly_data);
	screw2_transformPD->Update();

	this->m_style->screw2_poly_data = screw2_transformPD->GetOutput();

	this->m_style->callback1->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_1->setEnabled(1);

	this->m_style->callback2->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_2->setEnabled(1);

	this->m_style->callback3->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_3->setEnabled(1);

	this->qvtkWidget_1->GetRenderWindow()->Render();
	this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
	this->qvtkWidget_1->update();

	this->qvtkWidget_2->GetRenderWindow()->Render();
	this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
	this->qvtkWidget_2->update();

	this->qvtkWidget_3->GetRenderWindow()->Render();
	this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
	this->qvtkWidget_3->update();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}
}

void ProjectMainWindow::right_revision2()
{
	if (!this->m_style->finish)
		return;

	double dir_vectors[3] = { this->m_style->point->getPoint(4)[0] - this->m_style->point->getPoint(1)[0],
							  this->m_style->point->getPoint(4)[1] - this->m_style->point->getPoint(1)[1],
							  this->m_style->point->getPoint(4)[2] - this->m_style->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);

	double x_axis[3] = { this->m_style->planeNormal[0],this->m_style->planeNormal[1],this->m_style->planeNormal[2] };
	vtkMath::Normalize(x_axis);

	double y_axis[3] = { dir_vectors[0], dir_vectors[1],dir_vectors[2] };

	//畸变矫正
	double rate = x_axis[0] * dir_vectors[0] + x_axis[1] * dir_vectors[1] + x_axis[2] * dir_vectors[2];
	if (rate < 0)
	{
		dir_vectors[0] = -dir_vectors[0] / rate;
		dir_vectors[1] = -dir_vectors[1] / rate;
		dir_vectors[2] = -dir_vectors[2] / rate;

		y_axis[0] = x_axis[0] + dir_vectors[0];
		y_axis[1] = x_axis[1] + dir_vectors[1];
		y_axis[2] = x_axis[2] + dir_vectors[2];
	}
	else if (rate > 0)
	{
		dir_vectors[0] = dir_vectors[0] / rate;
		dir_vectors[1] = dir_vectors[1] / rate;
		dir_vectors[2] = dir_vectors[2] / rate;

		y_axis[0] = -x_axis[0] + dir_vectors[0];
		y_axis[1] = -x_axis[1] + dir_vectors[1];
		y_axis[2] = -x_axis[2] + dir_vectors[2];
	}

	vtkMath::Normalize(y_axis);

	double z_axis[3] = { (x_axis[1] * y_axis[2] - y_axis[1] * x_axis[2]),
						 (x_axis[2] * y_axis[0] - y_axis[2] * x_axis[0]),
						 (x_axis[0] * y_axis[1] - y_axis[0] * x_axis[1]) };
	vtkMath::Normalize(z_axis);


	double path3[3] = { this->m_style->finalPath[15] - this->m_style->finalPath[12],
						this->m_style->finalPath[16] - this->m_style->finalPath[13],
						this->m_style->finalPath[17] - this->m_style->finalPath[14] };
	double angle = -acos(-1) / 180;

	double rotateMatrix[3][3] =
	{ pow(y_axis[0],2) * (1 - cos(angle)) + cos(angle),y_axis[0] * y_axis[1] * (1 - cos(angle)) + y_axis[2] * sin(angle),y_axis[0] * y_axis[2] * (1 - cos(angle)) - y_axis[1] * sin(angle),

	 y_axis[0] * y_axis[1] * (1 - cos(angle)) - y_axis[2] * sin(angle),pow(y_axis[1],2) * (1 - cos(angle)) + cos(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) + y_axis[0] * sin(angle),

	 y_axis[0] * y_axis[2] * (1 - cos(angle)) + y_axis[1] * sin(angle),y_axis[1] * y_axis[2] * (1 - cos(angle)) - y_axis[0] * sin(angle), pow(y_axis[2],2) * (1 - cos(angle)) + cos(angle) };

	double new_path3[3] = { rotateMatrix[0][0] * path3[0] + rotateMatrix[0][1] * path3[1] + rotateMatrix[0][2] * path3[2],
							rotateMatrix[1][0] * path3[0] + rotateMatrix[1][1] * path3[1] + rotateMatrix[1][2] * path3[2],
							rotateMatrix[2][0] * path3[0] + rotateMatrix[2][1] * path3[1] + rotateMatrix[2][2] * path3[2] };

	double angle_with_middle = acos((new_path3[0] * this->m_style->planeNormal[0] + new_path3[1] * this->m_style->planeNormal[1] + new_path3[2] * this->m_style->planeNormal[2]) / vtkMath::Norm(new_path3));
	if (angle_with_middle * 180 / acos(-1) >= 15)
	{
		QMessageBox::warning(this, tr("warning"), tr("The angle between this screw and the middle peg exceeds 15 degree!"));
		return;
	}

	double intersect_ornot = new_path3[0] * dir_vectors[0] + new_path3[1] * dir_vectors[1] + new_path3[2] * dir_vectors[2];
	if (intersect_ornot < 0)
	{
		QMessageBox::warning(this, tr("warning"), tr("There may be interference  between the screw and the middle peg !"));
		return;
	}


	//double* origin = this->m_style->screw_actor1->GetOrigin();// [0] , m_style->base_actor->GetOrigin()[1], m_style->base_actor->GetOrigin()[1]};	
	this->m_style->screw_actor2->SetOrigin(this->m_style->point->getPoint(7));
	this->m_style->screw_actor2->RotateWXYZ(1, y_axis[0], y_axis[1], y_axis[2]);
	//this->m_style->screw_actor2->SetOrigin(this->m_style->spin_reference_point);

	double new_end_point3[3] = { this->m_style->finalPath[12] + new_path3[0],
								 this->m_style->finalPath[13] + new_path3[1],
								 this->m_style->finalPath[14] + new_path3[2] };
	this->m_style->finalPath[15] = new_end_point3[0];
	this->m_style->finalPath[16] = new_end_point3[1];
	this->m_style->finalPath[17] = new_end_point3[2];

	vtkSmartPointer<vtkTransform> screw_transform2 =
		vtkSmartPointer<vtkTransform>::New();
	screw_transform2->PostMultiply();
	screw_transform2->Translate(-this->m_style->finalPath[12], -this->m_style->finalPath[13], -this->m_style->finalPath[14]);
	/*double screw2_matrix[16] = { 0 };
	for (int i = 0;i < 3;i++)
	{
		screw2_matrix[i * 4 + 3] = this->m_style->finalPath[i + 12];
		for (int j = 0;j < 3;j++)
		{
			screw2_matrix[i * 4 + j] = rotateMatrix[i][j];
		}
	}
	screw2_matrix[15] = 1;
	screw_transform2->SetMatrix(screw2_matrix);*/
	screw_transform2->RotateWXYZ(1, y_axis[0], y_axis[1], y_axis[2]);
	screw_transform2->Translate(this->m_style->finalPath[12], this->m_style->finalPath[13], this->m_style->finalPath[14]);
	screw_transform2->Update();

	vtkSmartPointer<vtkTransformPolyDataFilter> screw2_transformPD =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	screw2_transformPD->SetTransform(screw_transform2);
	screw2_transformPD->SetInputData(this->m_style->screw2_poly_data);
	screw2_transformPD->Update();

	this->m_style->screw2_poly_data = screw2_transformPD->GetOutput();

	this->m_style->callback1->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_1->setEnabled(1);

	this->m_style->callback2->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_2->setEnabled(1);

	this->m_style->callback3->setProsthesis(this->m_style->base_poly_data, this->m_style->screw1_poly_data, this->m_style->screw2_poly_data, 1);
	this->horizontalSlider_3->setEnabled(1);

	this->qvtkWidget_1->GetRenderWindow()->Render();
	this->m_pRenderer1->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer1->GetActiveCamera()->SetParallelScale(this->m_style->callback1->ParallelScale);
	this->qvtkWidget_1->update();

	this->qvtkWidget_2->GetRenderWindow()->Render();
	this->m_pRenderer2->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer2->GetActiveCamera()->SetParallelScale(this->m_style->callback2->ParallelScale);
	this->qvtkWidget_2->update();

	this->qvtkWidget_3->GetRenderWindow()->Render();
	this->m_pRenderer3->GetActiveCamera()->SetParallelProjection(1);
	this->m_pRenderer3->GetActiveCamera()->SetParallelScale(this->m_style->callback3->ParallelScale);
	this->qvtkWidget_3->update();

	QElapsedTimer et;
	et.start();
	while (et.elapsed() < 25)
	{
		QApplication::processEvents();
	}
	this->operate_window->update();
}

void ProjectMainWindow::update()
{
	if (!this->m_style->finish)
		return;

	double  origin[3] = { 0 };
	double  spacing[3] = { 1 };
	double  bounds[6] = { 0 };
	this->m_style->boneIMGData->GetOrigin(origin);
	this->m_style->boneIMGData->GetSpacing(spacing);
	this->m_style->boneIMGData->GetBounds(bounds);

	double dir_1[3] = { this->m_style->finalPath[3] - this->m_style->finalPath[0],
						this->m_style->finalPath[4] - this->m_style->finalPath[1],
						this->m_style->finalPath[5] - this->m_style->finalPath[2] };

	double dir_2[3] = { this->m_style->finalPath[9] - this->m_style->finalPath[6],
						this->m_style->finalPath[10] - this->m_style->finalPath[7],
						this->m_style->finalPath[11] - this->m_style->finalPath[8] };

	double dir_3[3] = { this->m_style->finalPath[15] - this->m_style->finalPath[12],
						this->m_style->finalPath[16] - this->m_style->finalPath[13],
						this->m_style->finalPath[17] - this->m_style->finalPath[14] };
	vtkMath::Normalize(dir_1);
	vtkMath::Normalize(dir_2);
	vtkMath::Normalize(dir_3);

	this->optimalHu1 = 0;
	this->optimalHu2 = 0;
	for (int i = 1;i <= this->m_style->resolution[2];i++)
	{
		double pathCurPoint1[3] = { this->m_style->finalPath[0] + i * this->m_style->screwLen * dir_1[0] / this->m_style->resolution[2] ,
									this->m_style->finalPath[1] + i * this->m_style->screwLen * dir_1[1] / this->m_style->resolution[2] ,
									this->m_style->finalPath[2] + i * this->m_style->screwLen * dir_1[2] / this->m_style->resolution[2]  };
		pathCurPoint1[0] = round((pathCurPoint1[0] - origin[0]) / spacing[0]);
		pathCurPoint1[1] = round((pathCurPoint1[1] - origin[1]) / spacing[1]);
		pathCurPoint1[2] = round((pathCurPoint1[2] - origin[2]) / spacing[2]);
		int cur_hu1 = this->m_style->CTValueNormalize(*(int*)this->m_style->bone_img_cast->GetOutput()->GetScalarPointer(pathCurPoint1[0], pathCurPoint1[1], pathCurPoint1[2]));
		this->optimalHu1 += cur_hu1;

		double pathCurPoint2[3] = { this->m_style->finalPath[12] + i * this->m_style->screwLen * dir_3[0] / this->m_style->resolution[2] ,
									this->m_style->finalPath[13] + i * this->m_style->screwLen * dir_3[1] / this->m_style->resolution[2] ,
									this->m_style->finalPath[14] + i * this->m_style->screwLen * dir_3[2] / this->m_style->resolution[2]  };
		pathCurPoint2[0] = round((pathCurPoint2[0] - origin[0]) / spacing[0]);
		pathCurPoint2[1] = round((pathCurPoint2[1] - origin[1]) / spacing[1]);
		pathCurPoint2[2] = round((pathCurPoint2[2] - origin[2]) / spacing[2]);
		int cur_hu2 = this->m_style->CTValueNormalize(*(int*)this->m_style->bone_img_cast->GetOutput()->GetScalarPointer(pathCurPoint2[0], pathCurPoint2[1], pathCurPoint2[2]));
		this->optimalHu2 += cur_hu2;
	}

	this->output_pte->appendPlainText("\n*************************************");
	this->output_pte->appendPlainText("--start point and end point of path 1:");
	QString path1_start = QString::number(this->m_style->finalPath[0]);// +m_style->patient_origin[0]);//(m_style->finalPath[0] - origin[0]) / spacing[0]));
	path1_start.append("  ");
	path1_start.append(QString::number(this->m_style->finalPath[1]));//2 * m_style->bone_center[1] - m_style->finalPath[1] + m_style->patient_origin[1]));//(((m_style->finalPath[1] - origin[1]) / spacing[1])));
	path1_start.append("  ");
	path1_start.append(QString::number(this->m_style->finalPath[2]));//2 * m_style->bone_center[2] - m_style->finalPath[2] + m_style->patient_origin[2]));//(((m_style->finalPath[2] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path1_start);
	this->result_table->setItem(0, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[0])));// +m_style->patient_origin[0])));
	this->result_table->setItem(0, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[1])));//2 * m_style->bone_center[1] - m_style->finalPath[1] + m_style->patient_origin[1])));
	this->result_table->setItem(0, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[2])));//2 * m_style->bone_center[2] - m_style->finalPath[2] + m_style->patient_origin[2])));


	QString path1_end = QString::number(this->m_style->finalPath[3]);// +m_style->patient_origin[0]);//(((m_style->finalPath[3] - origin[0]) / spacing[0]));
	path1_end.append("  ");
	path1_end.append(QString::number(this->m_style->finalPath[4]));//2 * m_style->bone_center[1] - m_style->finalPath[4] + m_style->patient_origin[1]));//(((m_style->finalPath[4] - origin[1]) / spacing[1])));
	path1_end.append("  ");
	path1_end.append(QString::number(this->m_style->finalPath[5]));//2 * m_style->bone_center[2] - m_style->finalPath[5] + m_style->patient_origin[2]));//(((m_style->finalPath[5] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path1_end);
	double angle_1 = acos(dir_1[0] * dir_2[0] + dir_1[1] * dir_2[1] + dir_1[2] * dir_2[2]) * 180 / acos(-1);
	this->result_table->setItem(1, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[3])));// +m_style->patient_origin[0])));
	this->result_table->setItem(1, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[4])));//2 * m_style->bone_center[1] - m_style->finalPath[4] + m_style->patient_origin[1])));
	this->result_table->setItem(1, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[5])));//2 * m_style->bone_center[2] - m_style->finalPath[5] + m_style->patient_origin[2])));

	QString path1_angle = "angle with middle screw(degree):";
	path1_angle.append(QString::number(angle_1));
	this->output_pte->appendPlainText(path1_angle);
	QString Hu1 = "bone density index:";
	Hu1.append(QString::number(double(this->optimalHu1 / this->maxHu1)));
	/*Hu1.append("\tmax gray value integral of all paths:");
	Hu1.append(QString::number(this->maxHu1));*/
	this->output_pte->appendPlainText(Hu1);
	//path1_angle.append("°");



	this->output_pte->appendPlainText("\n--start point and end point of path 2:");
	QString path2_start = QString::number(this->m_style->finalPath[6]);// +m_style->patient_origin[0]);//(((m_style->finalPath[6] - origin[0]) / spacing[0]));
	path2_start.append("  ");
	path2_start.append(QString::number(this->m_style->finalPath[7]));//2 * m_style->bone_center[1] - m_style->finalPath[7] + m_style->patient_origin[1]));//(((m_style->finalPath[7] - origin[1]) / spacing[1])));
	path2_start.append("  ");
	path2_start.append(QString::number(this->m_style->finalPath[8]));//2 * m_style->bone_center[2] - m_style->finalPath[8] + m_style->patient_origin[2]));//(((m_style->finalPath[8] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path2_start);
	this->result_table->setItem(2, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[6])));// +m_style->patient_origin[0])));
	this->result_table->setItem(2, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[7])));//2 * m_style->bone_center[1] - m_style->finalPath[7] + m_style->patient_origin[1])));
	this->result_table->setItem(2, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[8])));//2 * m_style->bone_center[2] - m_style->finalPath[8] + m_style->patient_origin[2])));

	QString path2_end = QString::number(this->m_style->finalPath[9]);// +m_style->patient_origin[0]);//(((m_style->finalPath[9] - origin[0]) / spacing[0]));
	path2_end.append("  ");
	path2_end.append(QString::number(this->m_style->finalPath[10]));//2 * m_style->bone_center[1] - m_style->finalPath[10] + m_style->patient_origin[1]));//(((m_style->finalPath[10] - origin[1]) / spacing[1])));
	path2_end.append("  ");
	path2_end.append(QString::number(this->m_style->finalPath[11]));//2 * m_style->bone_center[2] - m_style->finalPath[11] + m_style->patient_origin[2]));//((m_style->finalPath[11] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path2_end);
	this->result_table->setItem(3, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[9])));// +m_style->patient_origin[0])));
	this->result_table->setItem(3, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[10])));//2 * m_style->bone_center[1] - m_style->finalPath[10] + m_style->patient_origin[1])));
	this->result_table->setItem(3, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[11])));//2 * m_style->bone_center[2] - m_style->finalPath[11] + m_style->patient_origin[2])));



	this->output_pte->appendPlainText("\n--start point and end point of path 3:");
	QString path3_start = QString::number(this->m_style->finalPath[12]);// +m_style->patient_origin[0]);//(((m_style->finalPath[12] - origin[0]) / spacing[0]));
	path3_start.append("  ");
	path3_start.append(QString::number(this->m_style->finalPath[13]));//2 * m_style->bone_center[1] - m_style->finalPath[13] + m_style->patient_origin[1]));//(((m_style->finalPath[13] - origin[1]) / spacing[1])));
	path3_start.append("  ");
	path3_start.append(QString::number(this->m_style->finalPath[14]));//2 * m_style->bone_center[2] - m_style->finalPath[14] + m_style->patient_origin[2]));//(((m_style->finalPath[14] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path3_start);
	this->result_table->setItem(4, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[12])));// +m_style->patient_origin[0])));
	this->result_table->setItem(4, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[13])));//2 * m_style->bone_center[1] - m_style->finalPath[13] + m_style->patient_origin[1])));
	this->result_table->setItem(4, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[14])));//2 * m_style->bone_center[2] - m_style->finalPath[14] + m_style->patient_origin[2])));

	QString path3_end = QString::number(this->m_style->finalPath[15]);// +m_style->patient_origin[0]);//(((m_style->finalPath[15] - origin[0]) / spacing[0]));
	path3_end.append("  ");
	path3_end.append(QString::number(this->m_style->finalPath[16]));//2 * m_style->bone_center[1] - m_style->finalPath[16] + m_style->patient_origin[1]));//(((m_style->finalPath[16] - origin[1]) / spacing[1])));
	path3_end.append("  ");
	path3_end.append(QString::number(this->m_style->finalPath[17]));//2 * m_style->bone_center[2] - m_style->finalPath[17] + m_style->patient_origin[2]));//(((m_style->finalPath[17] - origin[2]) / spacing[2])));
	this->output_pte->appendPlainText(path3_end);
	this->result_table->setItem(5, 0, new QTableWidgetItem(QString::number(this->m_style->finalPath[15])));// +m_style->patient_origin[0])));
	this->result_table->setItem(5, 1, new QTableWidgetItem(QString::number(this->m_style->finalPath[16])));//2 * m_style->bone_center[1] - m_style->finalPath[16] + m_style->patient_origin[1])));
	this->result_table->setItem(5, 2, new QTableWidgetItem(QString::number(this->m_style->finalPath[17])));//2 * m_style->bone_center[2] - m_style->finalPath[17] + m_style->patient_origin[2])));

	double angle_3 = acos(dir_3[0] * dir_2[0] + dir_3[1] * dir_2[1] + dir_3[2] * dir_2[2]) * 180 / acos(-1);
	QString path3_angle = "angle with middle screw(degree):";
	path3_angle.append(QString::number(angle_3));
	//path3_angle.append("°");
	this->output_pte->appendPlainText(path3_angle);
	QString Hu2 = "bone density index:";
	Hu2.append(QString::number(double(this->optimalHu2 / this->maxHu2)));
	/*Hu2.append("\tmax gray value integral of all paths:");
	Hu2.append(QString::number(this->maxHu2));*/
	this->output_pte->appendPlainText(Hu2);



	//double angle_1_3 = acos(dir_3[0] * dir_1[0] + dir_3[1] * dir_1[1] + dir_3[2] * dir_1[2]) * 180 / acos(-1);
	//QString path1_3_angle = "\n--angle between long screws(degree):";
	//path1_3_angle.append(QString::number(angle_1_3));
	//path1_3_angle.append("\n");
	////path3_angle.append("°");
	//this->output_pte->appendPlainText(path1_3_angle);
	this->output_pte->appendPlainText("*************************************");
	//this->output_pte->appendPlainText(QString::number(this->optimalHu1));
	//this->output_pte->appendPlainText(QString::number(this->optimalHu2));

	//this->m_style->callback1->setProsthesis(this->m_style->screw_actor1->GetMapper()->GetInput()->GetOutput(), screw1_transformPD->GetOutput(), screw2_transformPD->GetOutput(), 1);
	//this->horizontalSlider_1->setEnabled(1);


	//this->m_style->callback2->setProsthesis(middle_transformPD->GetOutput(), screw1_transformPD->GetOutput(), screw2_transformPD->GetOutput(), 1);
	//this->horizontalSlider_2->setEnabled(1);


	//this->m_style->callback3->setProsthesis(middle_transformPD->GetOutput(), screw1_transformPD->GetOutput(), screw2_transformPD->GetOutput(), 1);
	//this->horizontalSlider_3->setEnabled(1);

	//this->qvtkWidget_1->GetRenderWindow()->Render();
	////m_pRenderer1->ResetCamera();
	////m_pRenderer1->GetActiveCamera()->Zoom(1.5);
	//this->qvtkWidget_1->update();

	//this->qvtkWidget_2->GetRenderWindow()->Render();
	////m_pRenderer2->ResetCamera();
	////m_pRenderer2->GetActiveCamera()->Zoom(1.5);
	//this->qvtkWidget_2->update();

	//this->qvtkWidget_3->GetRenderWindow()->Render();
	////m_pRenderer3->ResetCamera();
	////m_pRenderer3->GetActiveCamera()->Zoom(1.5);
	//this->qvtkWidget_3->update();

	//QElapsedTimer et;
	//et.start();
	//while (et.elapsed() < 25)
	//{
	//	QApplication::processEvents();
	//}
	//progressEnd();
	//this->operate_window->update();
}