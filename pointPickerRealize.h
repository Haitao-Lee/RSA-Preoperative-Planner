#pragma once
#ifndef REALIZE_H
#define REALIZE_H
#include "PointPickerInteractorStyle.h"
#include <vtkConeSource.h>
#include <ProjectMainWindow.h>
#include <vtkOBBTree.h>
#include <vtkPointsProjectedHull.h>
#include <qapplication.h>

void PickerInteractorStyle::initialize(vtkPolyData* bonePolyData, vtkActor* boneActor, vtkImageData* bone_IMG_data, vtkImageCast* bone_img_cast, vtkPolyData* screw_data, vtkPolyData* base_data, int resolution[3], double angleOfDegree, double range[2], double bone_center[3], vtkPoints* extract_ps, vtkMarchingCubes* boneExtractor)
{
	this->point = new pointStore();
	this->pointNum = point->pointNum;
	//this->boneIMGData = boneIMGData;
	this->wholeBonePolyData = bonePolyData;
	this->curBonePolyData = bonePolyData;
	this->bone_cur_actor = boneActor;
	this->bone_origin_actor = boneActor;
	this->planeOrNot = false;
	this->segmentOrNot = false;
	this->finish = false;
	this->planeNormal[0] = 0;
	this->planeNormal[1] = 0;
	this->planeNormal[2] = 0;
	this->boneIMGData = bone_IMG_data;
	this->resolution[0] = resolution[0];
	this->resolution[1] = resolution[1];
	this->resolution[2] = resolution[2];
	this->angleOfDegree = angleOfDegree;
	this->screw_data = screw_data;
	this->base_data = base_data;
	this->clippedOrNot = false;
	this->bone_img_cast = bone_img_cast;
	this->range[0] = range[0];
	this->range[1] = range[1];
	this->plane = vtkSmartPointer<vtkPlane>::New();
	this->clip_actor1 = vtkSmartPointer<vtkActor>::New();
	this->clip_actor2 = vtkSmartPointer<vtkActor>::New();
	this->extract_points = vtkSmartPointer<vtkPoints>::New();
	this->extract_points = extract_ps;
	this->plane_actor = vtkSmartPointer<vtkActor>::New();
	this->bone_center[0] = bone_center[0];
	this->bone_center[1] = bone_center[1];
	this->bone_center[2] = bone_center[2];
	this->boneExtractor = boneExtractor;
	this->screw_apex_offset = 3.40;
	this->threshold_offset = 8;


	for (int i = 0;i < 18;i++)
		this->finalPath[i] = 0;

	//std::cout << "dicom schalar range:" << this->bone_img_cast->GetOutput()->GetScalarTypeMax() << " " << this->bone_img_cast->GetOutput()->GetScalarTypeMin() << std::endl;
	/*vtkSmartPointer<vtkPropPicker>  picker =
		vtkSmartPointer<vtkPropPicker>::New();
	picker->Pick(picked[0], picked[1], 0, this->GetDefaultRenderer());

	double* pos = picker->GetPickPosition();*/

	//vtkSmartPointer<vtkPolyDataNormals> boneDataFilter =
	//	vtkSmartPointer<vtkPolyDataNormals>::New();
	//boneDataFilter->SetInputData(this->bonePolyData);
	//boneDataFilter->SetComputePointNormals(0);
	//boneDataFilter->SetComputeCellNormals(0);
	//boneDataFilter->SetAutoOrientNormals(0);
	//boneDataFilter->SetSplitting(0);
	//boneDataFilter->Update();
	//pNormal = boneDataFilter->GetOutput()->GetPointData()->GetNormals();
	////std::cout << "number of cell: " << this->bonePolyData->GetNumberOfCells() << std::endl;
	//cNormal = boneDataFilter->GetOutput()->GetCellData()->GetNormals();
}


double* PickerInteractorStyle::getLastPicked()
{
	return this->point->getPoint(pointNum);
}



double* PickerInteractorStyle::getPicked(int rank)
{
	return this->point->getPoint(rank);
}




void PickerInteractorStyle::OnRightButtonDown()
{

	if (this->pointNum < 4)
	{
		//std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
		this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
			this->Interactor->GetEventPosition()[1],
			0,
			this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
		double picked[3] = { 0 };
		this->Interactor->GetPicker()->GetPickPosition(picked);
		//std::cout << "event position: " << picked[0] << " "<<picked[1] << " " <<picked[2] << " " << std::endl;
		this->point->addPoint(picked);
		this->pointNum++;
		pointVisualize(pointNum);
	}
	vtkInteractorStyleTrackballCamera::OnRightButtonDown();
}




void PickerInteractorStyle::OnRightButtonUp()
{
	/*if (pointNum == 3 && this->clippedOrNot == true)
	{
		vtkInteractorStyleTrackballCamera::OnRightButtonUp();
		return;
	}*/
	if (this->pointNum < 4)
	{
		vtkSmartPointer<vtkActorCollection> actorCollection = vtkSmartPointer<vtkActorCollection>::New();
		//std::cout << "Add this point(Y or N)?" << "  your answer:";
		/*std::string addPointOrNot;
		std::cin >> addPointOrNot;*/
		//std::cout << addPointOrNot << std::endl;
		/*if (addPointOrNot.compare("Y") == 0)
		{
			std::cout << " adding finish!" << std::endl;
			std::cout << " please picking next point." << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}*/

		/*else if (addPointOrNot.compare("N") == 0)
		{
			this->point->deleteLastPoint();
			this->pointNum--;
			actorCollection = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors();
			this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(actorCollection->GetLastActor());
			std::cout << "desert finish!" << std::endl;
			std::cout << " please picking next point." << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}*/
		/*else
		{
			this->point->deleteLastPoint();
			this->pointNum--;
			actorCollection = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors();
			this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(actorCollection->GetLastActor());
			std::cout << "input error!  adding failed!" << std::endl;
			std::cout << " please picking next point." << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
		}*/


		if (this->pointNum == 3)
		{
			//this->point->printSelf();
			if (this->planeOrNot == false)
			{
				//qDebug() << "visualize the cylinder!" << endl;
				vtkSmartPointer<vtkActorCollection> actor_collection = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors();
				this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(actor_collection->GetLastActor());
				actor_collection = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors();
				this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(actor_collection->GetLastActor());
				this->planeOrNot = true;

				normalVisualize(pointNum);
			}
			//std::cout << " please picking next point." << std::endl;
		}
		//std::cout << "pointStore num :" << this->point->pointNum << std::endl;
	}

	if (this->pointNum == 4)
	{
		this->spin_reference_point[0] = this->point->getPoint(1)[0];
		this->spin_reference_point[1] = this->point->getPoint(1)[1];
		this->spin_reference_point[2] = this->point->getPoint(1)[2];
		;		vtkSmartPointer<vtkActorCollection> actor_collection = this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->GetActors();
		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(actor_collection->GetLastActor());
		double dir_vectors[3] = { this->point->getPoint(4)[0] - this->point->getPoint(1)[0],
								  this->point->getPoint(4)[1] - this->point->getPoint(1)[1],
								  this->point->getPoint(4)[2] - this->point->getPoint(1)[2] };
		vtkMath::Normalize(dir_vectors);


		vtkMath::Normalize(this->planeNormal);

		//double middle_origin_apex[3] = { 13.58, 14.08, 14.14 };
		vtkSmartPointer<vtkTransform> middle_transform =
			vtkSmartPointer<vtkTransform>::New();
		//double middle_dir_vector[3] = { dir_vectors[0],dir_vectors[1], dir_vectors[2] };
		middle_transform->PostMultiply();


		double x_axis[3] = { this->planeNormal[0],this->planeNormal[1],this->planeNormal[2] };
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

		double matrix[16] = { x_axis[0], y_axis[0], z_axis[0], this->point->getPoint(1)[0],
							  x_axis[1], y_axis[1], z_axis[1], this->point->getPoint(1)[1],
							  x_axis[2], y_axis[2], z_axis[2], this->point->getPoint(1)[2],
							  0        , 0,          0,        1 };

		middle_transform->SetMatrix(matrix);


		middle_transform->Update();

		vtkSmartPointer<vtkTransformPolyDataFilter> middle_transformPD =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();
		middle_transformPD->SetTransform(middle_transform);
		middle_transformPD->SetInputData(this->base_data);

		vtkSmartPointer<vtkPolyDataMapper> middle_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		middle_mapper->SetInputConnection(middle_transformPD->GetOutputPort());

		vtkSmartPointer<vtkActor> middle_actor =
			vtkSmartPointer<vtkActor>::New();
		middle_actor->SetMapper(middle_mapper);
		middle_actor->GetProperty()->SetColor(0, 0.8, 0.8);
		middle_actor->GetProperty()->SetOpacity(1);
		middle_actor->SetVisibility(1);


		double new_point4[3] = { this->point->getPoint(1)[0] + y_axis[0], this->point->getPoint(1)[1] + y_axis[1], this->point->getPoint(1)[2] + y_axis[2] };
		this->point->changePoint(4, new_point4);

		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->RemoveActor(this->plane_actor);
		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(middle_actor);
		this->base_actor = middle_actor;


		dir_vectors[0] = this->point->getPoint(4)[0] - this->point->getPoint(1)[0];
		dir_vectors[1] = this->point->getPoint(4)[1] - this->point->getPoint(1)[1];
		dir_vectors[2] = this->point->getPoint(4)[2] - this->point->getPoint(1)[2];
		double point5[3] = { this->point->getPoint(1)[0] - dir_vectors[0] ,
							 this->point->getPoint(1)[1] - dir_vectors[1] ,
							 this->point->getPoint(1)[2] - dir_vectors[2] };
		this->point->addPoint(point5);
		this->pointNum++;

		double* inplant_point = this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5), this->screw_apex_offset);
		/*double inplant_point[9] = { this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5))[0],
									this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5))[1],
									this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5))[2],
									this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5))[3],
									this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5))[4],
									this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5))[5],
									this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5))[6],
									this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5))[7],
									this->inPlantPoint(this->distance, this->point->getPoint(1), this->point->getPoint(4), this->point->getPoint(5))[8] };*/

		this->finalPath[0] = inplant_point[0];
		this->finalPath[1] = inplant_point[1];
		this->finalPath[2] = inplant_point[2];
		this->finalPath[6] = inplant_point[3];
		this->finalPath[7] = inplant_point[4];
		this->finalPath[8] = inplant_point[5];
		this->finalPath[12] = inplant_point[6];
		this->finalPath[13] = inplant_point[7];
		this->finalPath[14] = inplant_point[8];

		this->screw_apex1[0] = inplant_point[0];
		this->screw_apex1[1] = inplant_point[1];
		this->screw_apex1[2] = inplant_point[2];
		this->screw_apex2[0] = inplant_point[6];
		this->screw_apex2[1] = inplant_point[7];
		this->screw_apex2[2] = inplant_point[8];

		this->point->addPoint(this->screw_apex1);
		this->pointNum++;
		this->point->addPoint(this->screw_apex2);
		this->pointNum++;

		vtkSmartPointer<vtkConeSource> cone1 =
			vtkSmartPointer<vtkConeSource>::New();
		cone1->SetHeight(this->screwLen);
		cone1->SetResolution(100);
		double cone_normal1[3] = { -this->planeNormal[0] ,-this->planeNormal[1] ,-this->planeNormal[2] };
		cone1->SetDirection(cone_normal1);
		double ag1 = this->angleOfDegree;
		double height1 = cone1->GetHeight();
		cone1->SetRadius(height1 * tan(ag1 * acos(-1) / 180));
		double center1[3] = { this->screw_apex1[0] + this->planeNormal[0] * screwLen / 2,this->screw_apex1[1] + this->planeNormal[1] * screwLen / 2,this->screw_apex1[2] + this->planeNormal[2] * screwLen / 2 };
		cone1->SetCenter(center1);
		cone1->Update();
		vtkSmartPointer<vtkPolyDataMapper>coneMapper1 =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		coneMapper1->SetInputConnection(cone1->GetOutputPort());
		vtkSmartPointer<vtkActor> actorCone1 =
			vtkSmartPointer<vtkActor>::New();
		actorCone1->SetMapper(coneMapper1);
		actorCone1->GetProperty()->SetColor(1.0, 0.0, 0.0);
		actorCone1->GetProperty()->SetOpacity(0.6);
		actorCone1->GetProperty()->SetEdgeColor(0.2, 0.8, 0.8);
		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actorCone1);
		this->actor_cone1 = actorCone1;



		vtkSmartPointer<vtkConeSource> cone2 =
			vtkSmartPointer<vtkConeSource>::New();
		cone2->SetHeight(this->screwLen);
		cone2->SetResolution(100);
		double cone_normal2[3] = { -this->planeNormal[0] ,-this->planeNormal[1] ,-this->planeNormal[2] };
		cone2->SetDirection(cone_normal2);
		double ag2 = this->angleOfDegree;
		double height2 = cone2->GetHeight();
		cone2->SetRadius(height2 * tan(ag2 * acos(-1) / 180));
		double center2[3] = { this->screw_apex2[0] + this->planeNormal[0] * this->screwLen / 2,this->screw_apex2[1] + this->planeNormal[1] * this->screwLen / 2,this->screw_apex2[2] + this->planeNormal[2] * this->screwLen / 2 };
		cone2->SetCenter(center2);
		cone2->Update();

		vtkSmartPointer<vtkPolyDataMapper>coneMapper2 =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		coneMapper2->SetInputConnection(cone2->GetOutputPort());

		vtkSmartPointer<vtkActor> actorCone2 =
			vtkSmartPointer<vtkActor>::New();
		actorCone2->SetMapper(coneMapper2);
		actorCone2->GetProperty()->SetColor(1.0, 0.0, 0.0);
		actorCone2->GetProperty()->SetOpacity(0.6);
		actorCone2->GetProperty()->SetEdgeColor(0.2, 0.8, 0.8);
		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actorCone2);
		this->actor_cone2 = actorCone2;
	}
	vtkInteractorStyleTrackballCamera::OnRightButtonUp();
	//vtkInteractorStyleTrackballCamera::OnLeftButtonUp();
}

void PickerInteractorStyle::OnLeftButtonDown()
{
	/*vtkSmartPointer<vtkCellPicker> picker =
		vtkSmartPointer<vtkCellPicker>::New();
	picker->Pick(this->Interactor->GetEventPosition()[0],
		this->Interactor->GetEventPosition()[1],
		0,
		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
	double picked[3] = { 0 };
	this->Interactor->GetPicker()->GetPickPosition(picked);

	if (this->boneIMGData != NULL && vtkMath::Norm(picked)!= 0)
	{
		this->callback1->ExecuteBy3DWindow(picked);
		this->callback2->ExecuteBy3DWindow(picked);
		this->callback3->ExecuteBy3DWindow(picked);
	}*/
	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void PickerInteractorStyle::OnMouseMove()
{
	//this->boneActor->GetProperty()->SetOpacity(1);
	vtkInteractorStyleTrackballCamera::OnMouseMove();
}


void PickerInteractorStyle::pointVisualize(int rank)
{
	double picked[3] = { this->point->getPoint(rank)[0],this->point->getPoint(rank)[1], this->point->getPoint(rank)[2] };
	//std::cout << "recorded picked:" << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

	vtkSmartPointer<vtkSphereSource> sphereSource =
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->Update();

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);
	actor->SetPosition(picked);
	actor->SetScale(2);
	actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
	if (this->pointNum == 1)
		this->middle_point_actor = actor;
	this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);
	double  origin[3] = { 0 };;
	double  spacing[3] = { 1 };
	double  bounds[6] = { 0 };
	this->boneIMGData->GetOrigin(origin);
	this->boneIMGData->GetSpacing(spacing);
	this->boneIMGData->GetBounds(bounds);

	/*double Hu_point[3] = { picked[0] * spacing[0] + origin[0],
						   picked[1] * spacing[1] + origin[1],
						   picked[2] * spacing[2] + origin[2] };*/
	double Hu_point[3] = { (picked[0] - origin[0]) / spacing[0],
						   (picked[1] - origin[1]) / spacing[1],
						   (picked[2] - origin[2]) / spacing[2] };

}






void PickerInteractorStyle::normalVisualize(int rank)
{
	double picked[3] = { this->point->getPoint(rank)[0],this->point->getPoint(rank)[1], this->point->getPoint(rank)[2] };
	vtkSmartPointer<vtkPropPicker>  picker =
		vtkSmartPointer<vtkPropPicker>::New();
	picker->Pick(picked[0], picked[1], 0, this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
	double* pos = picker->GetPickPosition();
	double planePoint0[3] = { 0 };
	double planePoint1[3] = { 0 };
	double planePoint2[3] = { 0 };
	double planeVectors01[3] = { 0 };
	double planeVectors02[3] = { 0 };
	double planeVectorSum01 = 0;
	double planeVectorSum02 = 0;
	for (int i = 0;i < 3;i++)
	{
		planePoint0[i] = point->getPoint(1)[i];
		//std::cout << "planePoint0[" << i << "]:" << planePoint0[i] << std::endl;
		planePoint1[i] = point->getPoint(2)[i];
		//std::cout << "planePoint1[" << i << "]:" << planePoint1[i] << std::endl;
		planePoint2[i] = point->getPoint(3)[i];
		//std::cout << "planePoint2[" << i << "]:" << planePoint2[i] << std::endl;
		planeVectors01[i] = planePoint1[i] - planePoint0[i];
		//std::cout << "planeVectors01[" << i << "]: " << planeVectors01[i] << std::endl;
		planeVectorSum01 += pow(planeVectors01[i], 2);
		//std::cout << " planeVectorSum01:" << planeVectorSum01 << std::endl;
		planeVectors02[i] = planePoint2[i] - planePoint0[i];
		planeVectorSum02 += pow(planeVectors02[i], 2);
		//std::cout << " planeVectorSum02:" << planeVectorSum02 << std::endl;
	}

	planeVectorSum01 = sqrt(planeVectorSum01);
	planeVectors01[0] = planeVectors01[0] / planeVectorSum01;
	planeVectors01[1] = planeVectors01[1] / planeVectorSum01;
	planeVectors01[2] = planeVectors01[2] / planeVectorSum01;

	planeVectorSum02 = sqrt(planeVectorSum02);
	planeVectors02[0] = planeVectors02[0] / planeVectorSum02;
	planeVectors02[1] = planeVectors02[1] / planeVectorSum02;
	planeVectors02[2] = planeVectors02[2] / planeVectorSum02;

	double planeNormal[3] =
	{
		planeVectors01[1] * planeVectors02[2] - planeVectors01[2] * planeVectors02[1],
		planeVectors01[2] * planeVectors02[0] - planeVectors01[0] * planeVectors02[2],
		planeVectors01[0] * planeVectors02[1] - planeVectors01[1] * planeVectors02[0],
	};
	//a2b3-a3b2,a3b1-a1b3,a1b2-a2b1



	vtkSmartPointer<vtkCylinderSource> cylinderSource =
		vtkSmartPointer<vtkCylinderSource>::New();
	cylinderSource->SetRadius(25);
	cylinderSource->SetCenter(0, 0, 0);
	cylinderSource->SetResolution(100);
	cylinderSource->SetHeight(0.5);
	cylinderSource->Update();
	vtkMath::Normalize(planeNormal);

	double* right_normal = this->normalInsight(planeNormal, this->point->getPoint(1), this->boneIMGData, this->screwLen);
	this->planeNormal[0] = right_normal[0];
	this->planeNormal[1] = right_normal[1];
	this->planeNormal[2] = right_normal[2];

	//Apply the transforms
	vtkSmartPointer<vtkTransform> transform =
		vtkSmartPointer<vtkTransform>::New();
	transform->PostMultiply();
	//transform->Translate(planePoint0);   // translate to starting point
	//transform->Concatenate(matrix);     // apply direction cosines
	vtkMath::Normalize(planeNormal);
	double rollZ = acos(abs(planeNormal[1])) * 180 / acos(-1);
	std::cout << "rollZ:" << rollZ << std::endl;
	transform->RotateZ(rollZ);
	double rollY = acos(abs(double(planeNormal[0]) / sqrt(1 - pow(planeNormal[1], 2)))) * 180 / acos(-1);
	std::cout << "rollY:" << rollY << std::endl;

	if (planeNormal[2] > 0 && planeNormal[1] > 0 && planeNormal[0] > 0)
		rollY = 180 - rollY;
	if (planeNormal[2] > 0 && planeNormal[1] > 0 && planeNormal[0] < 0)
		rollY = rollY;
	if (planeNormal[2] > 0 && planeNormal[1] < 0 && planeNormal[0] > 0)
		rollY = -rollY;
	if (planeNormal[2] > 0 && planeNormal[1] < 0 && planeNormal[0] < 0)
		rollY = rollY - 180;
	if (planeNormal[2] < 0 && planeNormal[1] > 0 && planeNormal[0] > 0)
		rollY = rollY - 180;
	if (planeNormal[2] < 0 && planeNormal[1] > 0 && planeNormal[0] < 0)
		rollY = -rollY;
	if (planeNormal[2] < 0 && planeNormal[1] < 0 && planeNormal[0] > 0)
		rollY = rollY;
	if (planeNormal[2] < 0 && planeNormal[1] < 0 && planeNormal[0] < 0)
		rollY = 180 - rollY;

	transform->RotateY(rollY);          // align cylinder to x axis
	transform->Translate(planePoint0);   // translate to starting point





	// Transform the polydata
	vtkSmartPointer<vtkTransformPolyDataFilter> transformPD =
		vtkSmartPointer<vtkTransformPolyDataFilter>::New();
	transformPD->SetTransform(transform);
	transformPD->SetInputConnection(cylinderSource->GetOutputPort());


	double newPoint1[3] = { 0 };
	double newPoint2[3] = { 0 };
	double planeLen = 40;
	for (int i = 0;i < 3;i++)
	{
		newPoint1[i] = planePoint0[i] + planeVectors01[i] * planeLen;
		newPoint2[i] = planePoint0[i] - planeVectors01[i] * planeLen;
	}

	double roll = acos(-1) / 4;

	double rotateMatrix[3][3] =
	{ pow(planeNormal[0],2) * (1 - cos(roll)) + cos(roll),planeNormal[0] * planeNormal[1] * (1 - cos(roll)) + planeNormal[2] * sin(roll),planeNormal[0] * planeNormal[2] * (1 - cos(roll)) - planeNormal[1] * sin(roll),

	 planeNormal[0] * planeNormal[1] * (1 - cos(roll)) - planeNormal[2] * sin(roll),pow(planeNormal[1],2) * (1 - cos(roll)) + cos(roll),planeNormal[1] * planeNormal[2] * (1 - cos(roll)) + planeNormal[0] * sin(roll),

	 planeNormal[0] * planeNormal[2] * (1 - cos(roll)) + planeNormal[1] * sin(roll),planeNormal[1] * planeNormal[2] * (1 - cos(roll)) - planeNormal[0] * sin(roll), pow(planeNormal[2],2) * (1 - cos(roll)) + cos(roll) };

	double planeVector[3] = { 0 };
	planeVector[0] = newPoint1[0] - planePoint0[0];
	planeVector[1] = newPoint1[1] - planePoint0[1];
	planeVector[2] = newPoint1[2] - planePoint0[2];

	double planeOriginVector[3] = { 0 };
	planeOriginVector[0] = planeVector[0] * rotateMatrix[0][0] + planeVector[1] * rotateMatrix[1][0] + planeVector[2] * rotateMatrix[2][0];
	planeOriginVector[1] = planeVector[1] * rotateMatrix[0][1] + planeVector[1] * rotateMatrix[1][1] + planeVector[2] * rotateMatrix[2][1];
	planeOriginVector[2] = planeVector[2] * rotateMatrix[0][2] + planeVector[1] * rotateMatrix[1][2] + planeVector[2] * rotateMatrix[2][2];

	double origin[3] = { 0 };
	origin[0] = planePoint0[0] + planeOriginVector[0];
	origin[1] = planePoint0[1] + planeOriginVector[1];
	origin[2] = planePoint0[2] + planeOriginVector[2];


	vtkSmartPointer<vtkPolyDataMapper> planeMapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	planeMapper->SetInputConnection(transformPD->GetOutputPort());
	//planeMapper->SetScalarRange(0, 7);


	vtkSmartPointer<vtkActor> planeActor =
		vtkSmartPointer<vtkActor>::New();
	planeActor->SetMapper(planeMapper);
	planeActor->GetProperty()->SetColor(0, 1, 0);
	planeActor->GetProperty()->SetOpacity(0.5);
	planeActor->GetProperty()->SetLineWidth(2);
	//planeActor->SetVisibility(1);
	planeActor->GetProperty()->EdgeVisibilityOn();

	this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(planeActor);
	this->plane_actor = planeActor;
	//std::cout << "plane is ready!" << std::endl;

}







vtkPoints* PickerInteractorStyle::coneGenerate(double screwApex[3], double normal[3], double screwLen, int resolution[3], double angleOfDegree, double vector[3])
{

	vtkMath::Normalize(normal);
	vtkSmartPointer<vtkConeSource> cone =
		vtkSmartPointer<vtkConeSource>::New();
	cone->SetHeight(screwLen);
	cone->SetResolution(100);
	/*normal[0] = -normal[0];
	normal[1] = -normal[1];
	normal[2] = -normal[2];*/
	double cone_normal[3] = { -normal[0] ,-normal[1] ,-normal[2] };
	cone->SetDirection(cone_normal);

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
	double baseCenter[3] = { screwApex[0] + normal[0] * screwLen ,screwApex[1] + normal[1] * screwLen ,screwApex[2] + normal[2] * screwLen };
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

	vtkPoints* p = vtkPoints::New();

	vtkSmartPointer<vtkCellArray> vertices =
		vtkSmartPointer<vtkCellArray>::New();

	p->InsertNextPoint(screwApex);
	//vertices->InsertNextCell(1, pid);
	//pid[0] = p->InsertNextPoint(baseCenter);
	//vertices->InsertNextCell(1, pid);
	//pid[0] = p->InsertNextPoint(center);
	//vertices->InsertNextCell(1, pid);
	p->InsertNextPoint(baseCenter);

	/*vtkSmartPointer<vtkLineSource> lineSource =
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
	actorLine->GetProperty()->SetLineWidth(5 * acos(-1) / resolution[0]);

	this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actorLine);*/

	/*vtkSmartPointer<vtkPolyData> pl =
		vtkSmartPointer<vtkPolyData>::New();*/

		//vtkSmartPointer<vtkPolyLine> line = 


		//vtkSmartPointer<vtkRenderer> ren = Render;
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
	//std::cout << baseVector[0] << baseVector[1] << baseVector[2] << std::endl;
	//std::cout << std::endl;
	vtkMath::Normalize(baseVector);

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
		double judege = baseVector[0] * vector[0] + baseVector[1] * vector[1] + baseVector[2] * vector[2];
		//double angle = acos()
		if (judege > 0)
		{
			continue;
		}
		//double newPoint[3] = { baseCenter[0] + baseVector[0] * radius,baseCenter[1]+baseVector[1] * radius ,baseCenter[2] +baseVector[2]* radius };
		//p->InsertNextPoint(newPoint);


		for (int k = 1;k < resolution[1] + 1;k++)
		{
			double rate = double(k) / double(resolution[1]);
			//std::cout << "rate:" << rate << std::endl;
			double radiusNewPoint[3] = { baseCenter[0] + baseVector[0] * radius * rate,baseCenter[1] + baseVector[1] * radius * rate ,baseCenter[2] + baseVector[2] * radius * rate };
			p->InsertNextPoint(radiusNewPoint);
			QApplication::processEvents();

			/*vtkSmartPointer<vtkLineSource> lineSource =
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

			this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actorLine);*/

			/*for (int t = 1;t < resolution[2];t++)
			{
				double apexVector[3] = { radiusNewPoint[0] - screwApex[0],radiusNewPoint[1] - screwApex[1], radiusNewPoint[2] - screwApex[2] };
				vtkMath::Normalize(apexVector);

				double calPoint[3] =
				{ screwApex[0] + apexVector[0] * screwLen * t / resolution[2],
				  screwApex[1] + apexVector[1] * screwLen * t / resolution[2],
				  screwApex[2] + apexVector[2] * screwLen * t / resolution[2] };
				p->InsertNextPoint(calPoint);
			}*/
			//std::cout << "radiusNewPoint: " << radiusNewPoint[0] << " " << radiusNewPoint[1] << " " << radiusNewPoint[2] << std::endl;
		}
	}


	//std::cout << "points of resolution is ready." << std::endl;
	int numOfPoint = p->GetNumberOfPoints() - 1;
	//std::cout << numOfPoint <<" "<< numOfLine << std::endl;
	for (int i = 0;i < numOfPoint;i++)
	{
		vtkSmartPointer<vtkPolyDataMapper>PointMapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();

		vtkSmartPointer<vtkSphereSource> sphere =
			vtkSmartPointer<vtkSphereSource>::New();
		sphere->SetCenter(p->GetPoint(i));
		//std::cout << "POINT[i]:" << POINT[i][0] << ',' << POINT[i][1] << ',' << POINT[i][2] << std::endl;
		sphere->SetRadius(5 * acos(-1) / resolution[0]);
		sphere->SetPhiResolution(10);
		sphere->SetThetaResolution(10);

		PointMapper->SetInputConnection(sphere->GetOutputPort());

		vtkSmartPointer<vtkActor> actorPoint =
			vtkSmartPointer<vtkActor>::New();
		actorPoint->SetMapper(PointMapper);
		actorPoint->GetProperty()->SetColor(0, 1.0, 0);
		//std::cout << "drawing sphere " << i << std::endl;
		//std::cout << " drawing sphere" << std::endl;
		//this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actorPoint);
	}

	//std::cout << "drawing finish." << std::endl;

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

	//vtkSmartPointer<vtkPolyDataMapper>coneMapper =
	//	vtkSmartPointer<vtkPolyDataMapper>::New();
	//coneMapper->SetInputConnection(cone->GetOutputPort());

	//vtkSmartPointer<vtkActor> actorCone =
	//	vtkSmartPointer<vtkActor>::New();
	//actorCone->SetMapper(coneMapper);
	//actorCone->GetProperty()->SetColor(1.0, 0.0, 0.0);
	//actorCone->GetProperty()->SetOpacity(0.4);
	////ctorCone->GetProperty()->SetEdgeVisibility(1);
	//actorCone->GetProperty()->SetEdgeColor(0.2, 0.8, 0.8);

	//this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actorCone);

	/*vtkSmartPointer<vtkLineSource> lineSource =
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
	this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actorLine);*/
	//std::cout << "return the points." << std::endl;
	return p;

}






//calculate the inplant points.
double* PickerInteractorStyle::inPlantPoint(double distance, double middlePoint[3], double reference_point1[3], double reference_point2[3],double screw_apex_offset)
{
	double vectors[3] = { reference_point1[0] - reference_point2[0],
						  reference_point1[1] - reference_point2[1],
						  reference_point1[2] - reference_point2[2] };

	vtkMath::Normalize(vectors);


	double inPlantPoint1[3] = { middlePoint[0] - vectors[0] * distance / 2 - this->screw_apex_offset * this->planeNormal[0],
								middlePoint[1] - vectors[1] * distance / 2 - this->screw_apex_offset * this->planeNormal[1],
								middlePoint[2] - vectors[2] * distance / 2 - this->screw_apex_offset * this->planeNormal[2] };

	double inPlantPoint2[3] = { middlePoint[0] + vectors[0] * distance / 2 - this->screw_apex_offset * this->planeNormal[0],
								middlePoint[1] + vectors[1] * distance / 2 - this->screw_apex_offset * this->planeNormal[1] ,
								middlePoint[2] + vectors[2] * distance / 2 - this->screw_apex_offset * this->planeNormal[2] };

	double inPlantPoint[9] = { inPlantPoint1[0],inPlantPoint1[1],inPlantPoint1[2] ,
							   middlePoint[0],  middlePoint[1],  middlePoint[2] ,
							   inPlantPoint2[0],inPlantPoint2[1],inPlantPoint2[2] };
	//this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->Ge
	return inPlantPoint;
}




//adjust the normal direction
double* PickerInteractorStyle::normalInsight(double normal[3], double startPoint[3], vtkImageData* bone_IMG_data, double screwLen)
{
	double insightNormal[3] = { normal[0],normal[1],normal[2] };
	vtkMath::Normalize(insightNormal);
	vtkImageData* bone_data = bone_IMG_data;
	int normal_threshold_down = 1;
	int normal_threshold_up = 6;
	int  normal_sum = 100;
	int Hu1 = 0;
	int Hu2 = 0;
	double  origin[3] = { 0 };
	double  spacing[3] = { 0 };
	double  bounds[6] = { 0 };
	this->boneIMGData->GetOrigin(origin);
	this->boneIMGData->GetSpacing(spacing);
	this->boneIMGData->GetBounds(bounds);

	for (int i = normal_threshold_down;i < normal_threshold_up;i++)
	{
		//std::cout << "Hu calculating:" << i << std::endl;

		double pathCurPoint1[3] = { startPoint[0] + insightNormal[0] * screwLen * i / normal_sum,
									startPoint[1] + insightNormal[1] * screwLen * i / normal_sum,
									startPoint[2] + insightNormal[2] * screwLen * i / normal_sum };
		/*pathCurPoint1[0] = round(pathCurPoint1[0] * spacing[0] + origin[0]);
		pathCurPoint1[1] = round(pathCurPoint1[1] * spacing[1] + origin[1]);
		pathCurPoint1[2] = round(pathCurPoint1[2] * spacing[2] + origin[2]);*/
		pathCurPoint1[0] = round((pathCurPoint1[0] - origin[0]) / spacing[0]);
		pathCurPoint1[1] = round((pathCurPoint1[1] - origin[1]) / spacing[1]);
		pathCurPoint1[2] = round((pathCurPoint1[2] - origin[2]) / spacing[2]);
		//std::cout << "Hu1:" << pathCurPoint1[0] << " " << pathCurPoint1[1] << " " << pathCurPoint1[2] << std::endl;
		Hu1 += CTValueNormalize(*(int*)this->bone_img_cast->GetOutput()->GetScalarPointer(pathCurPoint1[0], pathCurPoint1[1], pathCurPoint1[2]));



		double pathCurPoint2[3] = { startPoint[0] - insightNormal[0] * screwLen * i / normal_sum,
									startPoint[1] - insightNormal[1] * screwLen * i / normal_sum,
									startPoint[2] - insightNormal[2] * screwLen * i / normal_sum };
		/*pathCurPoint2[0] = round(pathCurPoint2[0] * spacing[0] + origin[0]);
		pathCurPoint2[1] = round(pathCurPoint2[1] * spacing[1] + origin[1]);
		pathCurPoint2[2] = round(pathCurPoint2[2] * spacing[2] + origin[2]);*/
		pathCurPoint2[0] = round((pathCurPoint2[0] - origin[0]) / spacing[0]);
		pathCurPoint2[1] = round((pathCurPoint2[1] - origin[1]) / spacing[1]);
		pathCurPoint2[2] = round((pathCurPoint2[2] - origin[2]) / spacing[2]);

		//std::cout << "Hu2:" << pathCurPoint2[0] << " " << pathCurPoint2[1] << " " << pathCurPoint2[2] << std::endl;
		Hu2 += CTValueNormalize(*(int*)this->bone_img_cast->GetOutput()->GetScalarPointer(pathCurPoint2[0], pathCurPoint2[1], pathCurPoint2[2]));


	}
	//std::cout << normal[0] << " " << normal[1] << " " << normal[2] << std::endl;
	//std::cout << " normal insight:" << Hu1 <<" " <<Hu2 << std::endl;
	if (Hu1 < Hu2)
	{
		insightNormal[0] = -insightNormal[0];
		insightNormal[1] = -insightNormal[1];
		insightNormal[2] = -insightNormal[2];
	}
	//std::cout << insightNormal[0] << " " << insightNormal[1] << " " << insightNormal[2] << std::endl;
	return insightNormal;
}



//generate the candidate path
double* PickerInteractorStyle::generatePath(vtkPoints* p, vtkImageData* bone_IMG_Data, double screwLen, int* resolution, int threshold)
{
	double screw_apex[3] = { p->GetPoint(0)[0],p->GetPoint(0)[1],p->GetPoint(0)[2] };
	double  origin[3] = { 0 };;
	double  spacing[3] = { 1 };
	double  bounds[6] = { 0 };
	bone_IMG_Data->GetOrigin(origin);
	bone_IMG_Data->GetSpacing(spacing);
	bone_IMG_Data->GetBounds(bounds);
	//get the information of dicom

	double optimizedPath[8] = { screw_apex[0],screw_apex[1],screw_apex[2],0,0,0,0,0 };
	int numOfPath = p->GetNumberOfPoints();
	double curStaility = 0;
	double lastStability = 0;
	double curHu = 0;
	double lastHu = 0;
	bool   safeOrNot = true;

	//添加左右、上下的判据,若未暴露，则左右上下均会存在密度较大骨壁，否则暴露
	double judge_offset = 0;
	double judge_dis = 10;
	double judge_num = 20;
	double dir_vectors[3] = { this->point->getPoint(4)[0] - this->point->getPoint(1)[0],
							  this->point->getPoint(4)[1] - this->point->getPoint(1)[1],
							  this->point->getPoint(4)[2] - this->point->getPoint(1)[2] };
	vtkMath::Normalize(dir_vectors);

	double side_judge_vector[3] = { this->planeNormal[1] * dir_vectors[2] - this->planeNormal[2] * dir_vectors[1],
									this->planeNormal[2] * dir_vectors[0] - this->planeNormal[0] * dir_vectors[2],
									this->planeNormal[0] * dir_vectors[1] - this->planeNormal[1] * dir_vectors[0] };
	vtkMath::Normalize(side_judge_vector);

	this->avail_path = 0;
	for (int i = 1;i < numOfPath;i++)
	{
		safeOrNot = true;
		double baseCurPoint[3] = { p->GetPoint(i)[0],p->GetPoint(i)[1],p->GetPoint(i)[2] };
		double pathVectors[3] = { baseCurPoint[0] - screw_apex[0],
								  baseCurPoint[1] - screw_apex[1],
								  baseCurPoint[2] - screw_apex[2] };

		vtkMath::Normalize(this->planeNormal);
		vtkMath::Normalize(pathVectors);

		curStaility = 0;
		curHu = 0;
		for (int j = 1;j <= resolution[2];j++)
		{
			double pathCurPoint[3] = { screw_apex[0] + pathVectors[0] * screwLen * j / resolution[2],
									   screw_apex[1] + pathVectors[1] * screwLen * j / resolution[2],
									   screw_apex[2] + pathVectors[2] * screwLen * j / resolution[2] };

			double roll = 2 * acos(-1) / 6;
			double screw_radius = 3;
			double rotateMatrix[3][3] =
			{ pow(pathVectors[0],2) * (1 - cos(roll)) + cos(roll),pathVectors[0] * pathVectors[1] * (1 - cos(roll)) + pathVectors[2] * sin(roll),pathVectors[0] * pathVectors[2] * (1 - cos(roll)) - pathVectors[1] * sin(roll),

			 pathVectors[0] * pathVectors[1] * (1 - cos(roll)) - pathVectors[2] * sin(roll),pow(pathVectors[1],2) * (1 - cos(roll)) + cos(roll),pathVectors[1] * pathVectors[2] * (1 - cos(roll)) + pathVectors[0] * sin(roll),

			 pathVectors[0] * pathVectors[2] * (1 - cos(roll)) + pathVectors[1] * sin(roll),pathVectors[1] * pathVectors[2] * (1 - cos(roll)) - pathVectors[0] * sin(roll), pow(pathVectors[2],2) * (1 - cos(roll)) + cos(roll) };

			double path_volum_vector[3] = { -pathVectors[2], 0, pathVectors[0] };
			vtkMath::Normalize(path_volum_vector);

			double newVector[3] = { 0 };
			if (j > resolution[2] / 8)
			{
				for (int k = 0;k < 6;k++)
				{
					if (!safeOrNot)
					{
						//this->text_out->appendPlainText("break!");
						break;
					}
					for (int m = 0;m < 3;m++)
					{
						newVector[m] = path_volum_vector[0] * rotateMatrix[0][m] + path_volum_vector[1] * rotateMatrix[1][m] + path_volum_vector[2] * rotateMatrix[2][m];
					}
					path_volum_vector[0] = newVector[0];
					path_volum_vector[1] = newVector[1];
					path_volum_vector[2] = newVector[2];
					vtkMath::Normalize(path_volum_vector);

					double screw_volum_point[3] = { pathCurPoint[0] + path_volum_vector[0] * screw_radius,pathCurPoint[1] + path_volum_vector[1] * screw_radius ,pathCurPoint[2] + path_volum_vector[2] * screw_radius };
					double screw_volum_ct_point[3] = { round((screw_volum_point[0] - origin[0]) / spacing[0]),
													   round((screw_volum_point[1] - origin[1]) / spacing[1]),
													   round((screw_volum_point[2] - origin[2]) / spacing[2]) };
					int Hu_volum = CTValueNormalize(*(int*)this->bone_img_cast->GetOutput()->GetScalarPointer(screw_volum_ct_point[0], screw_volum_ct_point[1], screw_volum_ct_point[2]));
					if (Hu_volum < threshold)
					{
						safeOrNot = false;
						bool judge_flag1 = false;
						bool judge_flag2 = false;
						bool judge_flag3 = false;
						bool judge_flag4 = false;
						//四面均有骨壁才算在骨内部
						for (int n = 0;n < judge_num;n++)
						{
							if (judge_flag1 == false)
							{
								double judge_p1[3] = { screw_volum_point[0] + dir_vectors[0] * judge_dis * n / judge_num,
													   screw_volum_point[1] + dir_vectors[1] * judge_dis * n / judge_num,
													   screw_volum_point[2] + dir_vectors[2] * judge_dis * n / judge_num };
								double judge_ct_point1[3] = { round((judge_p1[0] - origin[0]) / spacing[0]),
															  round((judge_p1[1] - origin[1]) / spacing[1]),
															  round((judge_p1[2] - origin[2]) / spacing[2]) };
								int Hu_judge1 = CTValueNormalize(*(int*)this->bone_img_cast->GetOutput()->GetScalarPointer(judge_ct_point1[0], judge_ct_point1[1], judge_ct_point1[2]));
								if (Hu_judge1 >= threshold + judge_offset)
								{
									//this->text_out->appendPlainText(QString::number(Hu_judge1));
									judge_flag1 = true;
								}
							}

							if (judge_flag2 == false)
							{
								double judge_p2[3] = { screw_volum_point[0] - dir_vectors[0] * judge_dis * n / judge_num,
													   screw_volum_point[1] - dir_vectors[1] * judge_dis * n / judge_num,
													   screw_volum_point[2] - dir_vectors[2] * judge_dis * n / judge_num };
								double judge_ct_point2[3] = { round((judge_p2[0] - origin[0]) / spacing[0]),
															  round((judge_p2[1] - origin[1]) / spacing[1]),
															  round((judge_p2[2] - origin[2]) / spacing[2]) };
								int Hu_judge2 = CTValueNormalize(*(int*)this->bone_img_cast->GetOutput()->GetScalarPointer(judge_ct_point2[0], judge_ct_point2[1], judge_ct_point2[2]));
								if (Hu_judge2 >= threshold + judge_offset)
								{
									//this->text_out->appendPlainText(QString::number(Hu_judge2));
									judge_flag2 = true;
								}
							}

							if (judge_flag3 == false)
							{
								double judge_p3[3] = { screw_volum_point[0] + side_judge_vector[0] * judge_dis * n / judge_num,
													   screw_volum_point[1] + side_judge_vector[1] * judge_dis * n / judge_num,
													   screw_volum_point[2] + side_judge_vector[2] * judge_dis * n / judge_num };
								double judge_ct_point3[3] = { round((judge_p3[0] - origin[0]) / spacing[0]),
															  round((judge_p3[1] - origin[1]) / spacing[1]),
															  round((judge_p3[2] - origin[2]) / spacing[2]) };
								int Hu_judge3 = CTValueNormalize(*(int*)this->bone_img_cast->GetOutput()->GetScalarPointer(judge_ct_point3[0], judge_ct_point3[1], judge_ct_point3[2]));
								if (Hu_judge3 >= threshold + judge_offset)
								{
									//this->text_out->appendPlainText(QString::number(Hu_judge3));
									judge_flag3 = true;

									/*vtkSmartPointer<vtkSphereSource> sphere =
										vtkSmartPointer<vtkSphereSource>::New();
									sphere->SetCenter(judge_p3);
									sphere->SetRadius(0.1);
									sphere->Update();

									vtkSmartPointer<vtkPolyDataMapper> testMapper3 =
										vtkSmartPointer<vtkPolyDataMapper>::New();
									testMapper3->SetInputData(sphere->GetOutput());

									vtkSmartPointer<vtkActor> testActor3 =
										vtkSmartPointer<vtkActor>::New();
									testActor3->SetMapper(testMapper3);
									testActor3->GetProperty()->SetColor(1, 0, 0);
									testActor3->GetProperty()->SetOpacity(1);
									this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(testActor3);*/
								}
							}

							if (judge_flag4 == false)
							{
								double judge_p4[3] = { screw_volum_point[0] - side_judge_vector[0] * judge_dis * n / judge_num,
													   screw_volum_point[1] - side_judge_vector[1] * judge_dis * n / judge_num,
													   screw_volum_point[2] - side_judge_vector[2] * judge_dis * n / judge_num };
								double judge_ct_point4[3] = { round((judge_p4[0] - origin[0]) / spacing[0]),
															  round((judge_p4[1] - origin[1]) / spacing[1]),
															  round((judge_p4[2] - origin[2]) / spacing[2]) };
								int Hu_judge4 = CTValueNormalize(*(int*)this->bone_img_cast->GetOutput()->GetScalarPointer(judge_ct_point4[0], judge_ct_point4[1], judge_ct_point4[2]));
								if (Hu_judge4 >= threshold + judge_offset)
								{
									//this->text_out->appendPlainText(QString::number(Hu_judge4));
									judge_flag4 = true;

								/*	vtkSmartPointer<vtkSphereSource> sphere =
										vtkSmartPointer<vtkSphereSource>::New();
									sphere->SetCenter(judge_p4);
									sphere->SetRadius(0.1);
									sphere->Update();

									vtkSmartPointer<vtkPolyDataMapper> testMapper3 =
										vtkSmartPointer<vtkPolyDataMapper>::New();
									testMapper3->SetInputData(sphere->GetOutput());

									vtkSmartPointer<vtkActor> testActor3 =
										vtkSmartPointer<vtkActor>::New();
									testActor3->SetMapper(testMapper3);
									testActor3->GetProperty()->SetColor(1, 0, 0);
									testActor3->GetProperty()->SetOpacity(1);
									this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(testActor3);*/
								}
							}

							/*QString flag;
								flag.append(QString::number(judge_flag1));
								flag.append(" ");
								flag.append(QString::number(judge_flag2));
								flag.append(" ");
								flag.append(QString::number(judge_flag3));
								flag.append(" ");
								flag.append(QString::number(judge_flag4));
								this->text_out->appendPlainText(flag);*/

							if (judge_flag1 && judge_flag2 && judge_flag3 && judge_flag4)
							{
								safeOrNot = true;
								//this->text_out->appendPlainText("\n\n");
								break;
								/*vtkSmartPointer<vtkSphereSource> sphere =
									vtkSmartPointer<vtkSphereSource>::New();
								sphere->SetCenter(pathCurPoint);
								sphere->SetRadius(1);
								sphere->Update();

								vtkSmartPointer<vtkPolyDataMapper> testMapper3 =
									vtkSmartPointer<vtkPolyDataMapper>::New();
								testMapper3->SetInputData(sphere->GetOutput());

								vtkSmartPointer<vtkActor> testActor3 =
									vtkSmartPointer<vtkActor>::New();
								testActor3->SetMapper(testMapper3);
								testActor3->GetProperty()->SetColor(1, 0, 0);
								testActor3->GetProperty()->SetOpacity(1);
								this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(testActor3);*/
							}
						}
					}
				}
			}

			pathCurPoint[0] = round((pathCurPoint[0] - origin[0]) / spacing[0]);
			pathCurPoint[1] = round((pathCurPoint[1] - origin[1]) / spacing[1]);
			pathCurPoint[2] = round((pathCurPoint[2] - origin[2]) / spacing[2]);

			int Hu = CTValueNormalize(*(int*)this->bone_img_cast->GetOutput()->GetScalarPointer(pathCurPoint[0], pathCurPoint[1], pathCurPoint[2]));
			curStaility += Hu;
			curHu += Hu;
		}

		if (curHu > lastHu)
		{
			lastHu = curHu;
		}

		if (safeOrNot)
		{
			this->avail_path++;
			if (curStaility > lastStability)
			{
				/*vtkSmartPointer<vtkLineSource> pathLine1 =
					vtkSmartPointer<vtkLineSource>::New();
				pathLine1->SetPoint1(p->GetPoint(i)[0], p->GetPoint(i)[1], p->GetPoint(i)[2]);
				pathLine1->SetPoint2(p->GetPoint(0)[0], p->GetPoint(0)[1], p->GetPoint(0)[2]);
				pathLine1->Update();

				vtkSmartPointer<vtkPolyDataMapper> path1_mapper =
					vtkSmartPointer<vtkPolyDataMapper>::New();
				path1_mapper->SetInputData(pathLine1->GetOutput());

				vtkSmartPointer<vtkActor> path1_actor =
					vtkSmartPointer<vtkActor>::New();
				path1_actor->SetMapper(path1_mapper);
				path1_actor->GetProperty()->SetColor(0, 1, 0);
				path1_actor->GetProperty()->SetLineWidth(2);
				this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(path1_actor);*/
				optimizedPath[3] = baseCurPoint[0];
				optimizedPath[4] = baseCurPoint[1];
				optimizedPath[5] = baseCurPoint[2];
				lastStability = curStaility;
				//this->text_out->appendPlainText(QString::number(lastStability));
				/*vtkSmartPointer<vtkSphereSource> sphere =
					vtkSmartPointer<vtkSphereSource>::New();
				sphere->SetCenter(baseCurPoint);
				sphere->SetRadius(1);
				sphere->Update();

				vtkSmartPointer<vtkPolyDataMapper> testMapper3 =
					vtkSmartPointer<vtkPolyDataMapper>::New();
				testMapper3->SetInputData(sphere->GetOutput());

				vtkSmartPointer<vtkActor> testActor3 =
					vtkSmartPointer<vtkActor>::New();
				testActor3->SetMapper(testMapper3);
				testActor3->GetProperty()->SetColor(1, 0, 0);
				testActor3->GetProperty()->SetOpacity(1);
				this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(testActor3);*/
			}
		}
		QApplication::processEvents();
	}
	optimizedPath[6] = lastStability;
	optimizedPath[7] = lastHu;
	return optimizedPath;
}

int PickerInteractorStyle::CTValueNormalize(double Hu)
{
	double rangeValue = this->range[1] - this->range[0];
	double rateValue = Hu - this->range[0];
	int newHu = round(rateValue * 255 / rangeValue);
	return newHu;
}
#endif // !REALIZE_H