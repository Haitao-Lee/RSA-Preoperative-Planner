#pragma once
#include "myReslice.h"
static vtkImageInteractionCallback* New()
{
	return new vtkImageInteractionCallback;
}

vtkImageInteractionCallback::vtkImageInteractionCallback()
{
	this->myCamera = vtkSmartPointer<vtkCamera>::New();
	this->contour_renderer = vtkSmartPointer<vtkRenderer>::New();
	this->Slicing = 0;
	this->ImageReslice = nullptr;
	this->img_ornot = 0;
	this->Interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
	this->picker = vtkSmartPointer<vtkCellPicker>::New();
}

void vtkImageInteractionCallback::SetImageReslice(vtkImageReslice* reslice)
{
	this->ImageReslice = reslice;
	this->img_ornot = 1;
}

void vtkImageInteractionCallback::SetMapToColors(vtkImageMapToColors* colors)
{
	this->MapToColors = colors;
}

void vtkImageInteractionCallback::SetInteractor(vtkRenderWindowInteractor* interactor)
{
	this->Interactor = interactor;
}

void vtkImageInteractionCallback::SetRenderWindow(vtkRenderWindow* window)
{
	this->RenderWindow = window;

	vtkMatrix4x4* matrix = this->ImageReslice->GetResliceAxes();
	if (matrix->GetElement(0, 2) != 0)
	{

		vtkSmartPointer<vtkTextActor> text_actor =
			vtkSmartPointer<vtkTextActor>::New();
		text_actor->SetInput("Sagittal section");
		//text_actor->SetTextScaleModeToProp();
		text_actor->SetTextScaleModeToNone();
		text_actor->GetProperty()->SetColor(1, 0, 0);
		text_actor->GetTextProperty()->SetFontSize(24);
		text_actor->GetTextProperty()->SetFontFamilyToArial();
		text_actor->GetTextProperty()->SetJustificationToLeft();
		text_actor->GetTextProperty()->BoldOn();
		//text_actor->GetTextProperty()->ItalicOn();
		text_actor->GetTextProperty()->ShadowOn();
		text_actor->SetDisplayPosition(5, 5);
		text_actor->GetActualPosition2Coordinate()->SetValue(0.6, 0.2);
		if (text_flag == 0)
		{
			this->image_renderer->AddViewProp(text_actor);
			text_flag = 1;
		}
		this->Interactor->Render();
		/*this->text->SetTextActor(text_actor);
		this->text->SetInteractor(this->Interactor);


		vtkSmartPointer<vtkTextRepresentation> text_r =
			vtkSmartPointer<vtkTextRepresentation>::New();
		text_r->GetPositionCoordinate()->SetValue(0, 0.75);
		text_r->GetPosition2Coordinate()->SetValue(0.7, 0.2);

		this->text->SetRepresentation(text_r);
		this->text->SetSelectable(1);*/
		//text->On();

	}

	else if (matrix->GetElement(1, 2) != 0)
	{
		vtkSmartPointer<vtkTextActor> text_actor =
			vtkSmartPointer<vtkTextActor>::New();
		text_actor->SetInput("Coronal section");
		//text_actor->SetTextScaleModeToProp();
		text_actor->SetTextScaleModeToNone();
		text_actor->GetProperty()->SetColor(0, 1, 0);
		text_actor->GetTextProperty()->SetFontSize(24);
		text_actor->GetTextProperty()->SetFontFamilyToArial();
		text_actor->GetTextProperty()->SetJustificationToLeft();
		text_actor->GetTextProperty()->BoldOn();
		//text_actor->GetTextProperty()->ItalicOn();
		text_actor->GetTextProperty()->ShadowOn();
		text_actor->SetDisplayPosition(5, 5);
		text_actor->GetActualPosition2Coordinate()->SetValue(0.6, 0.2);
		if (text_flag == 0)
		{
			this->image_renderer->AddViewProp(text_actor);
			text_flag = 1;
		}
		this->Interactor->Render();
		//this->text->SetTextActor(text_actor);
		//this->text->SetInteractor(this->Interactor);


		/*vtkSmartPointer<vtkTextRepresentation> text_r =
			vtkSmartPointer<vtkTextRepresentation>::New();
		text_r->GetPositionCoordinate()->SetValue(0, 0.75);
		text_r->GetPosition2Coordinate()->SetValue(0.7, 0.2);

		this->text->SetRepresentation(text_r);
		this->text->SetSelectable(1);*/
		//this->text->On();
	}

	else
	{
		vtkSmartPointer<vtkTextActor> text_actor =
			vtkSmartPointer<vtkTextActor>::New();
		text_actor->SetInput("Transverse section");
		//text_actor->SetTextScaleModeToProp();
		text_actor->SetTextScaleModeToNone();
		text_actor->GetProperty()->SetColor(0, 0, 1);
		text_actor->GetTextProperty()->SetFontSize(24);
		text_actor->GetTextProperty()->SetFontFamilyToArial();
		text_actor->GetTextProperty()->SetJustificationToLeft();
		text_actor->GetTextProperty()->BoldOn();
		//text_actor->GetTextProperty()->ItalicOn();
		text_actor->GetTextProperty()->ShadowOn();
		text_actor->SetDisplayPosition(5, 5);
		text_actor->GetActualPosition2Coordinate()->SetValue(0.6, 0.2);
		if (text_flag == 0)
		{
			this->image_renderer->AddViewProp(text_actor);
			text_flag = 1;

		}
		this->Interactor->Render();
		/*this->text->SetTextActor(text_actor);
		this->text->SetInteractor(this->Interactor);


		vtkSmartPointer<vtkTextRepresentation> text_r =
			vtkSmartPointer<vtkTextRepresentation>::New();
		text_r->GetPositionCoordinate()->SetValue(0, 0.75);
		text_r->GetPosition2Coordinate()->SetValue(0.7, 0.2);

		this->text->SetRepresentation(text_r);
		this->text->SetSelectable(1);*/
		//this->text->On();
	}
	this->image_renderer->UpdateLightsGeometryToFollowCamera();
	this->Interactor->Render();
	this->Interactor->GetRenderWindow()->StereoUpdate();
	this->Interactor->GetRenderWindow()->Render();
}


void vtkImageInteractionCallback::Execute(vtkObject* caller, unsigned long eventId, void* callData)
{
	if (img_ornot)
	{
		int lastPos[2], curPos[2];
		this->Interactor->GetLastEventPosition(lastPos);
		this->Interactor->GetEventPosition(curPos);
		vtkMatrix4x4* matrix = this->ImageReslice->GetResliceAxes();
		double normal[3] = { matrix->GetElement(0,2), matrix->GetElement(1,2), matrix->GetElement(2,2) };
		if (eventId == vtkCommand::LeftButtonPressEvent)
		{
			this->Slicing = 1;
			//去除原十字线
			this->contour_renderer->RemoveActor(this->x_line_actor);
			this->contour_renderer->RemoveActor(this->y_line_actor);
			this->Interactor->Render();
			//this->image_renderer->RemoveAllViewProps();

			this->picker->Pick(this->Interactor->GetEventPosition()[0],
				this->Interactor->GetEventPosition()[1],
				0,
				this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
			double picked[3] = { 0 };
			picker->GetPickPosition(picked);
			if (normal[0])
			{
				this->common_style->callback1->synWithOtherCallback(picked[1] - this->actor_center[1]);
				this->common_style->callback1->x_line_actor->AddPosition(0, picked[0] - this->y_line_actor->GetCenter()[0], 0);
				this->common_style->callback1->Interactor->Render();
				this->common_style->callback3->synWithOtherCallback(picked[0] - this->actor_center[1]);
				this->common_style->callback3->x_line_actor->AddPosition(0, picked[1] - this->x_line_actor->GetCenter()[1], 0);
				this->common_style->callback3->Interactor->Render();

				double x_p1[3] = { picked[0] - this->line_length,picked[1],0 };
				double x_p2[3] = { picked[0] + this->line_length,picked[1],0 };
				vtkSmartPointer<vtkLineSource>  x_line =
					vtkSmartPointer<vtkLineSource>::New();
				x_line->SetPoint1(x_p1);
				x_line->SetPoint2(x_p2);
				x_line->Update();

				vtkSmartPointer<vtkPolyDataMapper> x_line_mapper =
					vtkSmartPointer<vtkPolyDataMapper>::New();
				x_line_mapper->SetInputData(x_line->GetOutput());
				x_line_mapper->Update();

				vtkSmartPointer<vtkActor> x_line_actor =
					vtkSmartPointer<vtkActor>::New();
				x_line_actor->SetMapper(x_line_mapper);
				x_line_actor->GetProperty()->SetColor(0, 0, 1);
				x_line_actor->GetProperty()->SetLineWidth(this->line_width);

				double y_p1[3] = { picked[0],picked[1] - this->line_length,0 };
				double y_p2[3] = { picked[0],picked[1] + this->line_length,0 };
				vtkSmartPointer<vtkLineSource>  y_line =
					vtkSmartPointer<vtkLineSource>::New();
				y_line->SetPoint1(y_p1);
				y_line->SetPoint2(y_p2);
				y_line->Update();

				vtkSmartPointer<vtkPolyDataMapper> y_line_mapper =
					vtkSmartPointer<vtkPolyDataMapper>::New();
				y_line_mapper->SetInputData(y_line->GetOutput());
				y_line_mapper->Update();

				vtkSmartPointer<vtkActor> y_line_actor =
					vtkSmartPointer<vtkActor>::New();
				y_line_actor->SetMapper(y_line_mapper);
				y_line_actor->GetProperty()->SetColor(0, 1, 0);
				y_line_actor->GetProperty()->SetLineWidth(this->line_width);

				this->contour_renderer->AddActor(x_line_actor);
				this->contour_renderer->AddActor(y_line_actor);
				this->x_line_actor = x_line_actor;
				this->y_line_actor = y_line_actor;
				this->contour_renderer->DrawOn();
				this->contour_renderer->Modified();
			}
			else if (normal[1])
			{
				this->common_style->callback1->synWithOtherCallback(picked[1] - this->actor_center[1]);
				this->common_style->callback1->y_line_actor->AddPosition(picked[0] - this->y_line_actor->GetCenter()[0], 0, 0);
				this->common_style->callback1->Interactor->Render();
				this->common_style->callback2->synWithOtherCallback(picked[0] - this->actor_center[1]);
				this->common_style->callback2->x_line_actor->AddPosition(0, picked[1] - this->x_line_actor->GetCenter()[1], 0);
				this->common_style->callback2->Interactor->Render();

				double x_p1[3] = { picked[0] - this->line_length,picked[1],0 };
				double x_p2[3] = { picked[0] + this->line_length,picked[1],0 };
				vtkSmartPointer<vtkLineSource>  x_line =
					vtkSmartPointer<vtkLineSource>::New();
				x_line->SetPoint1(x_p1);
				x_line->SetPoint2(x_p2);
				x_line->Update();

				vtkSmartPointer<vtkPolyDataMapper> x_line_mapper =
					vtkSmartPointer<vtkPolyDataMapper>::New();
				x_line_mapper->SetInputData(x_line->GetOutput());
				x_line_mapper->Update();

				vtkSmartPointer<vtkActor> x_line_actor =
					vtkSmartPointer<vtkActor>::New();
				x_line_actor->SetMapper(x_line_mapper);
				x_line_actor->GetProperty()->SetColor(0, 0, 1);
				x_line_actor->GetProperty()->SetLineWidth(this->line_width);

				double y_p1[3] = { picked[0],picked[1] - this->line_length,0 };
				double y_p2[3] = { picked[0],picked[1] + this->line_length,0 };
				vtkSmartPointer<vtkLineSource>  y_line =
					vtkSmartPointer<vtkLineSource>::New();
				y_line->SetPoint1(y_p1);
				y_line->SetPoint2(y_p2);
				y_line->Update();

				vtkSmartPointer<vtkPolyDataMapper> y_line_mapper =
					vtkSmartPointer<vtkPolyDataMapper>::New();
				y_line_mapper->SetInputData(y_line->GetOutput());
				y_line_mapper->Update();

				vtkSmartPointer<vtkActor> y_line_actor =
					vtkSmartPointer<vtkActor>::New();
				y_line_actor->SetMapper(y_line_mapper);
				y_line_actor->GetProperty()->SetColor(1, 0, 0);
				y_line_actor->GetProperty()->SetLineWidth(this->line_width);

				this->contour_renderer->AddActor(x_line_actor);
				this->contour_renderer->AddActor(y_line_actor);
				this->x_line_actor = x_line_actor;
				this->y_line_actor = y_line_actor;
				this->contour_renderer->DrawOn();
				this->contour_renderer->Modified();
			}
			else
			{
				this->common_style->callback2->synWithOtherCallback(picked[0] - this->actor_center[1]);
				this->common_style->callback2->y_line_actor->AddPosition(picked[1] - this->x_line_actor->GetCenter()[1], 0, 0);
				this->common_style->callback2->Interactor->Render();
				this->common_style->callback3->synWithOtherCallback(picked[1] - this->actor_center[1]);
				this->common_style->callback3->y_line_actor->AddPosition(picked[0] - this->y_line_actor->GetCenter()[0], 0, 0);
				this->common_style->callback3->Interactor->Render();
				double x_p1[3] = { picked[0] - this->line_length,picked[1],0 };
				double x_p2[3] = { picked[0] + this->line_length,picked[1],0 };
				vtkSmartPointer<vtkLineSource>  x_line =
					vtkSmartPointer<vtkLineSource>::New();
				x_line->SetPoint1(x_p1);
				x_line->SetPoint2(x_p2);
				x_line->Update();

				vtkSmartPointer<vtkPolyDataMapper> x_line_mapper =
					vtkSmartPointer<vtkPolyDataMapper>::New();
				x_line_mapper->SetInputData(x_line->GetOutput());
				x_line_mapper->Update();

				vtkSmartPointer<vtkActor> x_line_actor =
					vtkSmartPointer<vtkActor>::New();
				x_line_actor->SetMapper(x_line_mapper);
				x_line_actor->GetProperty()->SetColor(0, 1, 0);
				x_line_actor->GetProperty()->SetLineWidth(this->line_width);

				double y_p1[3] = { picked[0],picked[1] - this->line_length,0 };
				double y_p2[3] = { picked[0],picked[1] + this->line_length,0 };
				vtkSmartPointer<vtkLineSource>  y_line =
					vtkSmartPointer<vtkLineSource>::New();
				y_line->SetPoint1(y_p1);
				y_line->SetPoint2(y_p2);
				y_line->Update();

				vtkSmartPointer<vtkPolyDataMapper> y_line_mapper =
					vtkSmartPointer<vtkPolyDataMapper>::New();
				y_line_mapper->SetInputData(y_line->GetOutput());
				y_line_mapper->Update();

				vtkSmartPointer<vtkActor> y_line_actor =
					vtkSmartPointer<vtkActor>::New();
				y_line_actor->SetMapper(y_line_mapper);
				y_line_actor->GetProperty()->SetColor(1, 0, 0);
				y_line_actor->GetProperty()->SetLineWidth(this->line_width);

				this->contour_renderer->AddActor(x_line_actor);
				this->contour_renderer->AddActor(y_line_actor);
				this->x_line_actor = x_line_actor;
				this->y_line_actor = y_line_actor;
				this->contour_renderer->DrawOn();
				this->contour_renderer->Modified();
			}
			this->Interactor->Render();
			this->last_picked[0] = picked[0];
			this->last_picked[1] = picked[1];
		}
		else if (eventId == vtkCommand::LeftButtonReleaseEvent)
		{

			this->Slicing = 0;
		}
		else if (eventId == vtkCommand::MouseMoveEvent)
		{
			if (this->Slicing)
			{
				int deltaY = lastPos[1] - curPos[1];
				this->ImageReslice->Update();

				double point[4], center[4];
				point[0] = 0.0;
				point[1] = 0.0;
				point[2] = deltaY * this->change_rate;
				point[3] = 1.0;

				matrix->MultiplyPoint(point, center);
				matrix->SetElement(0, 3, center[0]);
				matrix->SetElement(1, 3, center[1]);
				matrix->SetElement(2, 3, center[2]);
				this->change_rate = 1;
				if (normal[0])
				{
					this->common_style->callback1->y_line_actor->AddPosition(point[2], 0, 0);
					this->common_style->callback1->Interactor->Render();
					this->common_style->callback3->y_line_actor->AddPosition(point[2], 0, 0);
					this->common_style->callback3->Interactor->Render();
				}
				else if (normal[1])
				{
					this->common_style->callback1->x_line_actor->AddPosition(0, point[2], 0);
					this->common_style->callback1->Interactor->Render();
					this->common_style->callback2->y_line_actor->AddPosition(point[2], 0, 0);
					this->common_style->callback2->Interactor->Render();
				}
				else
				{
					this->common_style->callback2->x_line_actor->AddPosition(0, point[2], 0);
					this->common_style->callback2->Interactor->Render();
					this->common_style->callback3->x_line_actor->AddPosition(0, point[2], 0);
					this->common_style->callback3->Interactor->Render();
				}
				if (rm_ornot)
				{
					this->contour_renderer->RemoveAllViewProps();
					this->contour_renderer->AddActor(this->x_line_actor);
					this->contour_renderer->AddActor(this->y_line_actor);
					//this->image_renderer->RemoveAllViewProps();
				}
				if (this->prosthesisOrNot)
				{
					this->change_rate = 0.1;
					double minBound[3];
					minBound[0] = this->prosthesis_base->GetBounds()[0];
					minBound[1] = this->prosthesis_base->GetBounds()[2];
					minBound[2] = this->prosthesis_base->GetBounds()[4];

					//得到输入的STL模型的最小大坐标
					double maxBound[3];
					maxBound[0] = this->prosthesis_base->GetBounds()[1];
					maxBound[1] = this->prosthesis_base->GetBounds()[3];
					maxBound[2] = this->prosthesis_base->GetBounds()[5];


					vtkSmartPointer<vtkPlane> plane =
						vtkSmartPointer<vtkPlane>::New();
					plane->SetOrigin(center);
					plane->SetNormal(normal[0], normal[1], normal[2]);

					//去掉原来的切片;
					//this->contour_renderer->RemoveAllViewProps();

					//创建模型切割器
					vtkSmartPointer<vtkCutter> cutter_base =
						vtkSmartPointer<vtkCutter>::New();
					cutter_base->SetCutFunction(plane);//设置切割平面
					cutter_base->SetInputData(this->prosthesis_base);//设置模型



					vtkSmartPointer<vtkCutter> cutter_screw1 =
						vtkSmartPointer<vtkCutter>::New();
					cutter_screw1->SetCutFunction(plane);//设置切割平面
					cutter_screw1->SetInputData(this->screw1);//设置模型

					vtkSmartPointer<vtkCutter> cutter_screw2 =
						vtkSmartPointer<vtkCutter>::New();
					cutter_screw2->SetCutFunction(plane);//设置切割平面
					cutter_screw2->SetInputData(this->screw2);//设置模型

					double* space = this->ImageReslice->GetOutput()->GetSpacing();
					double* origin = this->ImageReslice->GetOutput()->GetOrigin();

					double* prothesis_center = this->prosthesis_base->GetCenter();//this->prothesis->GetOutput()->GetCenter();
					double cutter_pos[3] = { 0 };

					vtkSmartPointer<vtkTransform> plane_transform_base =
						vtkSmartPointer<vtkTransform>::New();
					vtkSmartPointer<vtkTransform> plane_transform_screw1 =
						vtkSmartPointer<vtkTransform>::New();
					vtkSmartPointer<vtkTransform> plane_transform_screw2 =
						vtkSmartPointer<vtkTransform>::New();

					vtkSmartPointer<vtkTransformPolyDataFilter> plane_transformPD_base =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();
					vtkSmartPointer<vtkTransformPolyDataFilter> plane_transformPD_screw1 =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();
					vtkSmartPointer<vtkTransformPolyDataFilter> plane_transformPD_screw2 =
						vtkSmartPointer<vtkTransformPolyDataFilter>::New();
					plane_transform_screw1->PostMultiply();
					plane_transform_screw2->PostMultiply();
					plane_transform_base->PostMultiply();

					if (normal[0])    //sagital面
					{
						double prothesis_pos[3] = { prothesis_center[1] - actor_center[1] ,
													prothesis_center[2] - actor_center[2] ,
													-prothesis_center[0] + actor_center[0] + offset };

						cutter_pos[0] = prothesis_pos[0];
						cutter_pos[1] = prothesis_pos[1];
						cutter_pos[2] = prothesis_pos[2];


						plane_transform_base->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
						plane_transform_screw1->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
						plane_transform_screw2->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
						plane_transform_base->RotateY(90);
						plane_transform_screw1->RotateY(90);
						plane_transform_screw2->RotateY(90);
						plane_transform_base->RotateZ(-90);
						plane_transform_screw1->RotateZ(-90);
						plane_transform_screw2->RotateZ(-90);
						plane_transform_base->Scale(1, -1, 1);
						plane_transform_screw1->Scale(1, -1, 1);
						plane_transform_screw2->Scale(1, -1, 1);
						plane_transform_base->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
						plane_transform_screw1->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
						plane_transform_screw2->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
					}
					else if (normal[1])   //cornal面
					{

						double prothesis_pos[3] = { prothesis_center[0] - actor_center[0],
													prothesis_center[2] - actor_center[2] ,
													-prothesis_center[1] + actor_center[1] + offset };

						cutter_pos[0] = prothesis_pos[0];
						cutter_pos[1] = prothesis_pos[1];
						cutter_pos[2] = prothesis_pos[2];

						plane_transform_base->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
						plane_transform_screw1->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
						plane_transform_screw2->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
						plane_transform_base->RotateX(90);
						plane_transform_screw1->RotateX(90);
						plane_transform_screw2->RotateX(90);
						plane_transform_base->Scale(1, -1, 1);
						plane_transform_screw1->Scale(1, -1, 1);
						plane_transform_screw2->Scale(1, -1, 1);
						plane_transform_base->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
						plane_transform_screw1->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
						plane_transform_screw2->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
					}
					else    //transverse面
					{
						double prothesis_pos[3] = { prothesis_center[0] - this->actor_center[0],
													prothesis_center[1] - this->actor_center[1] ,
													prothesis_center[2] - this->actor_center[2] + offset };// +origin[2]

						cutter_pos[0] = prothesis_pos[0];
						cutter_pos[1] = prothesis_pos[1];
						cutter_pos[2] = prothesis_pos[2];

						plane_transform_base->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
						plane_transform_screw1->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
						plane_transform_screw2->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);

						plane_transform_base->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
						plane_transform_screw1->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);//z不对
						plane_transform_screw2->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);//z不对
					}

					plane_transform_screw1->Update();
					plane_transform_screw2->Update();
					plane_transform_base->Update();

					plane_transformPD_base->SetInputConnection(cutter_base->GetOutputPort());
					plane_transformPD_base->SetTransform(plane_transform_base);

					plane_transformPD_screw1->SetTransform(plane_transform_screw1);
					plane_transformPD_screw1->SetInputConnection(cutter_screw1->GetOutputPort());
					plane_transformPD_screw2->SetTransform(plane_transform_screw2);
					plane_transformPD_screw2->SetInputConnection(cutter_screw2->GetOutputPort());

					vtkSmartPointer<vtkPolyDataMapper> cutterMapper_base =
						vtkSmartPointer<vtkPolyDataMapper>::New();
					cutterMapper_base->SetInputConnection(plane_transformPD_base->GetOutputPort());

					vtkSmartPointer<vtkActor> cutter_plane_actor_base =
						vtkSmartPointer<vtkActor>::New();
					cutter_plane_actor_base->GetProperty()->SetColor(0, 1, 1);
					cutter_plane_actor_base->GetProperty()->SetLineWidth(5);
					cutter_plane_actor_base->SetMapper(cutterMapper_base);
					cutter_plane_actor_base->Modified();

					vtkSmartPointer<vtkPolyDataMapper> cutterMapper_screw1 =
						vtkSmartPointer<vtkPolyDataMapper>::New();
					cutterMapper_screw1->SetInputConnection(plane_transformPD_screw1->GetOutputPort());

					vtkSmartPointer<vtkPolyDataMapper> cutterMapper_screw2 =
						vtkSmartPointer<vtkPolyDataMapper>::New();
					cutterMapper_screw2->SetInputConnection(plane_transformPD_screw2->GetOutputPort());

					vtkSmartPointer<vtkActor> cutter_plane_actor_screw1 =
						vtkSmartPointer<vtkActor>::New();
					cutter_plane_actor_screw1->GetProperty()->SetColor(1, 1, 0);
					cutter_plane_actor_screw1->GetProperty()->SetLineWidth(5);
					cutter_plane_actor_screw1->SetMapper(cutterMapper_screw1);
					cutter_plane_actor_screw1->Modified();


					vtkSmartPointer<vtkActor> cutter_plane_actor_screw2 =
						vtkSmartPointer<vtkActor>::New();
					cutter_plane_actor_screw2->GetProperty()->SetColor(0, 1, 0);
					cutter_plane_actor_screw2->GetProperty()->SetLineWidth(5);
					cutter_plane_actor_screw2->SetMapper(cutterMapper_screw2);
					cutter_plane_actor_screw2->Modified();


					this->contour_renderer->AddActor(cutter_plane_actor_base);
					this->contour_renderer->AddActor(cutter_plane_actor_screw1);
					this->contour_renderer->AddActor(cutter_plane_actor_screw2);

					this->contour_renderer->DrawOn();
					this->contour_renderer->Modified();

					if (rm_ornot == 0)
					{
						this->rm_ornot = 1;
					}
				}
				this->MapToColors->Update();
				this->OutputImageData = this->MapToColors->GetOutput();
				this->Interactor->Render();
			}
			else
			{
				vtkInteractorStyle* style = vtkInteractorStyle::SafeDownCast(this->Interactor->GetInteractorStyle());
				if (style)
					style->OnMouseMove();
			}
		}
	}
}

void vtkImageInteractionCallback::synWithOtherCallback(double depth)
{
	vtkMatrix4x4* matrix = this->ImageReslice->GetResliceAxes();
	double normal[3] = { matrix->GetElement(0,2), matrix->GetElement(1,2), matrix->GetElement(2,2) };
	matrix->SetElement(0, 3, this->actor_center[0]);
	matrix->SetElement(1, 3, this->actor_center[1]);
	matrix->SetElement(2, 3, this->actor_center[2]);

	/*double spacing = 0;
	if (normal[0])
		spacing = this->ImageReslice->GetOutput()->GetSpacing()[0];
	else if (normal[1])
		spacing = this->ImageReslice->GetOutput()->GetSpacing()[1];
	else
		spacing = this->ImageReslice->GetOutput()->GetSpacing()[2];*/

	double point[4], center[4];
	point[0] = 0.0;
	point[1] = 0.0;
	point[2] = depth;
	point[3] = 1.0;

	matrix->MultiplyPoint(point, center);
	matrix->SetElement(0, 3, center[0]);
	matrix->SetElement(1, 3, center[1]);
	matrix->SetElement(2, 3, center[2]);

	this->ImageReslice->Update();

	if (rm_ornot)
	{
		this->contour_renderer->RemoveAllViewProps();
		this->contour_renderer->AddActor(this->x_line_actor);
		this->contour_renderer->AddActor(this->y_line_actor);
		//this->image_renderer->RemoveAllViewProps();
	}
	if (this->prosthesisOrNot)
	{
		this->change_rate = 0.1;
		double minBound[3];
		minBound[0] = this->prosthesis_base->GetBounds()[0];
		minBound[1] = this->prosthesis_base->GetBounds()[2];
		minBound[2] = this->prosthesis_base->GetBounds()[4];

		//得到输入的STL模型的最小大坐标
		double maxBound[3];
		maxBound[0] = this->prosthesis_base->GetBounds()[1];
		maxBound[1] = this->prosthesis_base->GetBounds()[3];
		maxBound[2] = this->prosthesis_base->GetBounds()[5];


		vtkSmartPointer<vtkPlane> plane =
			vtkSmartPointer<vtkPlane>::New();
		plane->SetOrigin(center);
		plane->SetNormal(abs(normal[0]), abs(normal[1]), abs(normal[2]));

		//去掉原来的切片;
		//this->contour_renderer->RemoveAllViewProps();

		//创建模型切割器
		vtkSmartPointer<vtkCutter> cutter_base =
			vtkSmartPointer<vtkCutter>::New();
		cutter_base->SetCutFunction(plane);//设置切割平面
		cutter_base->SetInputData(this->prosthesis_base);//设置模型



		vtkSmartPointer<vtkCutter> cutter_screw1 =
			vtkSmartPointer<vtkCutter>::New();
		cutter_screw1->SetCutFunction(plane);//设置切割平面
		cutter_screw1->SetInputData(this->screw1);//设置模型

		vtkSmartPointer<vtkCutter> cutter_screw2 =
			vtkSmartPointer<vtkCutter>::New();
		cutter_screw2->SetCutFunction(plane);//设置切割平面
		cutter_screw2->SetInputData(this->screw2);//设置模型

		double* space = this->ImageReslice->GetOutput()->GetSpacing();
		double* origin = this->ImageReslice->GetOutput()->GetOrigin();

		double* prothesis_center = this->prosthesis_base->GetCenter();//this->prothesis->GetOutput()->GetCenter();
		double cutter_pos[3] = { 0 };

		vtkSmartPointer<vtkTransform> plane_transform_base =
			vtkSmartPointer<vtkTransform>::New();
		vtkSmartPointer<vtkTransform> plane_transform_screw1 =
			vtkSmartPointer<vtkTransform>::New();
		vtkSmartPointer<vtkTransform> plane_transform_screw2 =
			vtkSmartPointer<vtkTransform>::New();

		vtkSmartPointer<vtkTransformPolyDataFilter> plane_transformPD_base =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();
		vtkSmartPointer<vtkTransformPolyDataFilter> plane_transformPD_screw1 =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();
		vtkSmartPointer<vtkTransformPolyDataFilter> plane_transformPD_screw2 =
			vtkSmartPointer<vtkTransformPolyDataFilter>::New();
		plane_transform_screw1->PostMultiply();
		plane_transform_screw2->PostMultiply();
		plane_transform_base->PostMultiply();

		if (normal[0] != 0)    //sagital面
		{
			double prothesis_pos[3] = { prothesis_center[1] - actor_center[1] ,
										prothesis_center[2] - actor_center[2] ,
										-prothesis_center[0] + actor_center[0] + offset };

			cutter_pos[0] = prothesis_pos[0];
			cutter_pos[1] = prothesis_pos[1];
			cutter_pos[2] = prothesis_pos[2];


			plane_transform_base->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
			plane_transform_screw1->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
			plane_transform_screw2->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
			plane_transform_base->RotateY(90);
			plane_transform_screw1->RotateY(90);
			plane_transform_screw2->RotateY(90);
			plane_transform_base->RotateZ(-90);
			plane_transform_screw1->RotateZ(-90);
			plane_transform_screw2->RotateZ(-90);
			plane_transform_base->Scale(1, -1, 1);
			plane_transform_screw1->Scale(1, -1, 1);
			plane_transform_screw2->Scale(1, -1, 1);
			plane_transform_base->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
			plane_transform_screw1->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
			plane_transform_screw2->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);

		}
		if (normal[1] != 0)   //cornal面
		{

			double prothesis_pos[3] = { prothesis_center[0] - actor_center[0],
										prothesis_center[2] - actor_center[2] ,
										-prothesis_center[1] + actor_center[1] + offset };

			cutter_pos[0] = prothesis_pos[0];
			cutter_pos[1] = prothesis_pos[1];
			cutter_pos[2] = prothesis_pos[2];

			plane_transform_base->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
			plane_transform_screw1->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
			plane_transform_screw2->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
			plane_transform_base->RotateX(90);
			plane_transform_screw1->RotateX(90);
			plane_transform_screw2->RotateX(90);
			plane_transform_base->Scale(1, -1, 1);
			plane_transform_screw1->Scale(1, -1, 1);
			plane_transform_screw2->Scale(1, -1, 1);
			plane_transform_base->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
			plane_transform_screw1->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
			plane_transform_screw2->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
		}
		if (normal[2] != 0)   //transverse面
		{
			double prothesis_pos[3] = { prothesis_center[0] - this->actor_center[0],
										prothesis_center[1] - this->actor_center[1] ,
										prothesis_center[2] - this->actor_center[2] + offset };// +origin[2]

			cutter_pos[0] = prothesis_pos[0];
			cutter_pos[1] = prothesis_pos[1];
			cutter_pos[2] = prothesis_pos[2];

			plane_transform_base->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
			plane_transform_screw1->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);
			plane_transform_screw2->Translate(-prothesis_center[0], -prothesis_center[1], -prothesis_center[2]);

			plane_transform_base->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);
			plane_transform_screw1->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);//z不对
			plane_transform_screw2->Translate(prothesis_pos[0], prothesis_pos[1], prothesis_pos[2]);//z不对
		}

		plane_transform_screw1->Update();
		plane_transform_screw2->Update();
		plane_transform_base->Update();

		plane_transformPD_base->SetInputConnection(cutter_base->GetOutputPort());
		plane_transformPD_base->SetTransform(plane_transform_base);

		plane_transformPD_screw1->SetTransform(plane_transform_screw1);
		plane_transformPD_screw1->SetInputConnection(cutter_screw1->GetOutputPort());
		plane_transformPD_screw2->SetTransform(plane_transform_screw2);
		plane_transformPD_screw2->SetInputConnection(cutter_screw2->GetOutputPort());

		vtkSmartPointer<vtkPolyDataMapper> cutterMapper_base =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		cutterMapper_base->SetInputConnection(plane_transformPD_base->GetOutputPort());

		vtkSmartPointer<vtkActor> cutter_plane_actor_base =
			vtkSmartPointer<vtkActor>::New();
		cutter_plane_actor_base->GetProperty()->SetColor(0, 1, 1);
		cutter_plane_actor_base->GetProperty()->SetLineWidth(5);
		cutter_plane_actor_base->SetMapper(cutterMapper_base);
		cutter_plane_actor_base->Modified();

		vtkSmartPointer<vtkPolyDataMapper> cutterMapper_screw1 =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		cutterMapper_screw1->SetInputConnection(plane_transformPD_screw1->GetOutputPort());

		vtkSmartPointer<vtkPolyDataMapper> cutterMapper_screw2 =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		cutterMapper_screw2->SetInputConnection(plane_transformPD_screw2->GetOutputPort());

		vtkSmartPointer<vtkActor> cutter_plane_actor_screw1 =
			vtkSmartPointer<vtkActor>::New();
		cutter_plane_actor_screw1->GetProperty()->SetColor(1, 1, 0);
		cutter_plane_actor_screw1->GetProperty()->SetLineWidth(5);
		cutter_plane_actor_screw1->SetMapper(cutterMapper_screw1);
		cutter_plane_actor_screw1->Modified();


		vtkSmartPointer<vtkActor> cutter_plane_actor_screw2 =
			vtkSmartPointer<vtkActor>::New();
		cutter_plane_actor_screw2->GetProperty()->SetColor(0, 1, 0);
		cutter_plane_actor_screw2->GetProperty()->SetLineWidth(5);
		cutter_plane_actor_screw2->SetMapper(cutterMapper_screw2);
		cutter_plane_actor_screw2->Modified();


		this->contour_renderer->AddActor(cutter_plane_actor_base);
		this->contour_renderer->AddActor(cutter_plane_actor_screw1);
		this->contour_renderer->AddActor(cutter_plane_actor_screw2);

		this->contour_renderer->DrawOn();
		this->contour_renderer->Modified();

		if (rm_ornot == 0)
		{
			this->rm_ornot = 1;
		}
	}
	this->MapToColors->Update();
	this->OutputImageData = this->MapToColors->GetOutput();
	this->Interactor->Render();
}

void vtkImageInteractionCallback::setProsthesis(vtkPolyData* b, vtkPolyData* s1, vtkPolyData* s2, vtkTypeBool flag)
{
	this->prosthesis_base = b;
	this->screw1 = s1;
	this->screw2 = s2;
	this->prosthesisOrNot = flag;
	this->rm_ornot = 0;
	this->image_renderer->SetActiveCamera(this->myCamera);
}

void vtkImageInteractionCallback::setImageData(vtkImageData* boneImgData, double dcm_center[3], vtkRenderer* image_renderer, PickerInteractorStyle* common_style)
{
	this->boneIMGData = boneImgData;
	this->image_renderer = image_renderer;
	this->text_flag = 0;
	this->common_style = common_style;
	//this->myCamera->SetParallelProjection(1);//设置平行投影
	this->myCamera->SetParallelScale(ParallelScale);
	this->image_renderer->SetActiveCamera(this->myCamera);
	this->image_renderer->ResetCamera();
	//this->image_renderer->GetActiveCamera()->Zoom(zoom_rate);
	this->change_rate = 1;
	this->actor_center[0] = dcm_center[0];
	this->actor_center[1] = dcm_center[1];
	this->actor_center[2] = dcm_center[2];
	this->contour_renderer->RemoveAllViewProps();
	this->contour_renderer->SetActiveCamera(this->myCamera);
	this->Interactor->GetRenderWindow()->AddRenderer(this->contour_renderer);
	this->Interactor->GetRenderWindow()->SetNumberOfLayers(2);
	this->image_renderer->SetLayer(0);
	this->contour_renderer->SetLayer(1);

	vtkMatrix4x4* matrix = this->ImageReslice->GetResliceAxes();
	double normal[3] = { matrix->GetElement(0,2), matrix->GetElement(1,2), matrix->GetElement(2,2) };
	this->line_origin[0] = 0;//matrix->GetElement(0, 3);
	this->line_origin[1] = 0;//matrix->GetElement(1, 3);
	this->last_picked[0] = this->line_origin[0];
	this->last_picked[1] = this->line_origin[1];
	this->picked_before = false;
	if (normal[0])
	{
		double x_p1[3] = { line_origin[0] - this->line_length,line_origin[1],0 };
		double x_p2[3] = { line_origin[0] + this->line_length,line_origin[1],0 };
		vtkSmartPointer<vtkLineSource>  x_line =
			vtkSmartPointer<vtkLineSource>::New();
		x_line->SetPoint1(x_p1);
		x_line->SetPoint2(x_p2);
		x_line->Update();

		vtkSmartPointer<vtkPolyDataMapper> x_line_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		x_line_mapper->SetInputData(x_line->GetOutput());
		x_line_mapper->Update();

		vtkSmartPointer<vtkActor> x_line_actor =
			vtkSmartPointer<vtkActor>::New();
		x_line_actor->SetMapper(x_line_mapper);
		x_line_actor->GetProperty()->SetColor(0, 0, 1);
		x_line_actor->GetProperty()->SetLineWidth(this->line_width);

		double y_p1[3] = { line_origin[0],line_origin[1] - this->line_length,0 };
		double y_p2[3] = { line_origin[0],line_origin[1] + this->line_length,0 };
		vtkSmartPointer<vtkLineSource>  y_line =
			vtkSmartPointer<vtkLineSource>::New();
		y_line->SetPoint1(y_p1);
		y_line->SetPoint2(y_p2);
		y_line->Update();

		vtkSmartPointer<vtkPolyDataMapper> y_line_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		y_line_mapper->SetInputData(y_line->GetOutput());
		y_line_mapper->Update();

		vtkSmartPointer<vtkActor> y_line_actor =
			vtkSmartPointer<vtkActor>::New();
		y_line_actor->SetMapper(y_line_mapper);
		y_line_actor->GetProperty()->SetColor(0, 1, 0);
		y_line_actor->GetProperty()->SetLineWidth(this->line_width);

		this->contour_renderer->AddActor(x_line_actor);
		this->contour_renderer->AddActor(y_line_actor);
		this->x_line_actor = x_line_actor;
		this->y_line_actor = y_line_actor;
		this->contour_renderer->DrawOn();
		this->contour_renderer->Modified();
	}
	else if (normal[1])
	{
		double x_p1[3] = { line_origin[0] - this->line_length,line_origin[1],0 };
		double x_p2[3] = { line_origin[0] + this->line_length,line_origin[1],0 };
		vtkSmartPointer<vtkLineSource>  x_line =
			vtkSmartPointer<vtkLineSource>::New();
		x_line->SetPoint1(x_p1);
		x_line->SetPoint2(x_p2);
		x_line->Update();

		vtkSmartPointer<vtkPolyDataMapper> x_line_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		x_line_mapper->SetInputData(x_line->GetOutput());
		x_line_mapper->Update();

		vtkSmartPointer<vtkActor> x_line_actor =
			vtkSmartPointer<vtkActor>::New();
		x_line_actor->SetMapper(x_line_mapper);
		x_line_actor->GetProperty()->SetColor(0, 0, 1);
		x_line_actor->GetProperty()->SetLineWidth(this->line_width);

		double y_p1[3] = { line_origin[0],line_origin[1] - this->line_length,0 };
		double y_p2[3] = { line_origin[0],line_origin[1] + this->line_length,0 };
		vtkSmartPointer<vtkLineSource>  y_line =
			vtkSmartPointer<vtkLineSource>::New();
		y_line->SetPoint1(y_p1);
		y_line->SetPoint2(y_p2);
		y_line->Update();

		vtkSmartPointer<vtkPolyDataMapper> y_line_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		y_line_mapper->SetInputData(y_line->GetOutput());
		y_line_mapper->Update();

		vtkSmartPointer<vtkActor> y_line_actor =
			vtkSmartPointer<vtkActor>::New();
		y_line_actor->SetMapper(y_line_mapper);
		y_line_actor->GetProperty()->SetColor(1, 0, 0);
		y_line_actor->GetProperty()->SetLineWidth(this->line_width);

		this->contour_renderer->AddActor(x_line_actor);
		this->contour_renderer->AddActor(y_line_actor);
		this->x_line_actor = x_line_actor;
		this->y_line_actor = y_line_actor;
		this->contour_renderer->DrawOn();
		this->contour_renderer->Modified();
	}
	else
	{
		double x_p1[3] = { line_origin[0] - this->line_length,line_origin[1],0 };
		double x_p2[3] = { line_origin[0] + this->line_length,line_origin[1],0 };
		vtkSmartPointer<vtkLineSource>  x_line =
			vtkSmartPointer<vtkLineSource>::New();
		x_line->SetPoint1(x_p1);
		x_line->SetPoint2(x_p2);
		x_line->Update();

		vtkSmartPointer<vtkPolyDataMapper> x_line_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		x_line_mapper->SetInputData(x_line->GetOutput());
		x_line_mapper->Update();

		vtkSmartPointer<vtkActor> x_line_actor =
			vtkSmartPointer<vtkActor>::New();
		x_line_actor->SetMapper(x_line_mapper);
		x_line_actor->GetProperty()->SetColor(0, 1, 0);
		x_line_actor->GetProperty()->SetLineWidth(this->line_width);

		double y_p1[3] = { line_origin[0],line_origin[1] - this->line_length,0 };
		double y_p2[3] = { line_origin[0],line_origin[1] + this->line_length,0 };
		vtkSmartPointer<vtkLineSource>  y_line =
			vtkSmartPointer<vtkLineSource>::New();
		y_line->SetPoint1(y_p1);
		y_line->SetPoint2(y_p2);
		y_line->Update();

		vtkSmartPointer<vtkPolyDataMapper> y_line_mapper =
			vtkSmartPointer<vtkPolyDataMapper>::New();
		y_line_mapper->SetInputData(y_line->GetOutput());
		y_line_mapper->Update();

		vtkSmartPointer<vtkActor> y_line_actor =
			vtkSmartPointer<vtkActor>::New();
		y_line_actor->SetMapper(y_line_mapper);
		y_line_actor->GetProperty()->SetColor(1, 0, 0);
		y_line_actor->GetProperty()->SetLineWidth(this->line_width);

		this->contour_renderer->AddActor(x_line_actor);
		this->contour_renderer->AddActor(y_line_actor);
		this->x_line_actor = x_line_actor;
		this->y_line_actor = y_line_actor;
		this->contour_renderer->DrawOn();
		this->contour_renderer->Modified();
	}
	this->Interactor->Render();
}


void vtkImageInteractionCallback::setSlider(QSlider* slider)
{
	this->slider = slider;
}



