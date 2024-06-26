#pragma once
#include "vtkSmartPointer.h"
#include "vtkMatrix4x4.h"
#include "vtkDICOMImageReader.h"
#include "vtkImageData.h"
#include "vtkImageReslice.h"
#include "vtkLookupTable.h"
#include "vtkImageMapToColors.h"
#include "vtkImageActor.h"
#include "vtkImageMapper3D.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleImage.h"
#include <vtkPolyDataMapper.h>
#include "vtkCommand.h"
#include <vtkCutter.h>
#include <vtkPlane.h>
#include <vtkActor.h>
#include <vtkActor2D.h>
#include <vtkPolyDataMapper2D.h>
#include <vtkProperty2D.h>
#include <vtkActor2DCollection.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkCamera.h>
#include <vtkTextWidget.h>
#include <vtkTextActor.h>
#include <vtkTextRepresentation.h>
#include <vtkTextProperty.h>
#include <vtkViewport.h>
#include <vtkPolyDataToImageStencil.h>
#include <vtkResliceCursorWidget.h>
#include <vtkAppendPolyData.h>
#include <qslider.h>
#include <vtkAxesActor.h>
#include <vtkLineSource.h>
#include <vtkRendererCollection.h>
#include <vtkCollectionIterator.h>
#include <vtkCellPicker.h>
#include <vtkProperty.h>
#include <PointPickerInteractorStyle.h>