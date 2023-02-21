#pragma once
#include <vtkImageViewer2.h>
#include <vtkSmartPointer.h>
#include <vtkDICOMImageReader.h>


class myImageViewer2D :public vtkImageViewer2
{
public: 
	static myImageViewer2D* New()
	{
		return new myImageViewer2D;
	}

    virtual void setSlice(int slice)

    {
        int* range = this->GetSliceRange();
        if (range)
        {
            if (slice < range[0])
            {
                slice = range[0];
            }
            else if (slice > range[1])
            {
                slice = range[1];
            }
        }

        if (this->Slice == slice)
        {
            return;
        }

        this->Slice = slice;
        this->Modified();

        this->UpdateDisplayExtent();
        //this->Render();
    }
       
};