#pragma once
#include <ProjectMainWindowRealize.h>
#include <pointPickerRealize.h>
#include <PointPickerInteractorStyle.h>
#include <qfuture.h>
#include <QtConcurrent/qtconcurrentrun.h>

/***************************************
* 目前该头文件定义的函数用不上，仅作链接作用
********************************************/


void ProjectMainWindow::lamda_onOpenSlot()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::onOpenSlot);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_undoLastOperation()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::undoLastOperation);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_clipOrNot()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::clipOrNot);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_clip()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::clip);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_changeClippingArea()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::changeClippingArea);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_changeThreshold()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::changeThreshold);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_on_plainTextEdit_customContextMenuRequested(const QPoint& pos)
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::on_plainTextEdit_customContextMenuRequested,pos);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_path_display()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::path_display);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_onReadmeDialog()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::onReadmeDialog);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_onRevisionDialog()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::onRevisionDialog);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_connect_first()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::connect_first);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_segment()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::segment);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


//void ProjectMainWindow::lamda_rightOrLeft()
//{
//    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::rightOrLeft);
//    while (!future.isFinished())
//    {
//        QApplication::processEvents(QEventLoop::AllEvents, 100);
//    }
//}
//
//
//void ProjectMainWindow::lamda_leftOrRight()
//{
//    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::leftOrRight);
//    while (!future.isFinished())
//    {
//        QApplication::processEvents(QEventLoop::AllEvents, 100);
//    }
//}


void ProjectMainWindow::lamda_ajustOpacity()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::ajustOpacity);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_change_iso_value()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::change_iso_value);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_min_slider_window_syn()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::min_slider_window_syn);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_min_box_window_syn()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::min_box_window_syn);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_max_slider_window_syn()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::max_slider_window_syn);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_max_box_window_syn()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::max_box_window_syn);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_setSlice1()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::setSlice1);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_setSlice2()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::setSlice2);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_setSlice3()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::setSlice3);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_in_revision()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::in_revision);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void ProjectMainWindow::lamda_out_revision()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::out_revision);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_up_revision()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::up_revision);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_down_revision()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::down_revision);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_left_revision()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::left_revision);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_right_revision()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::right_revision);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_l_r_revision()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::l_r_revision);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

void ProjectMainWindow::lamda_u_d_revision()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::u_d_revision);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_spin_revision()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::spin_revision);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_l_r_syn()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::l_r_syn);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_u_d_syn()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::u_d_syn);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_spin_syn()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::spin_syn);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_onRebuildDialog()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::onRebuildDialog);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_onSaveOBJDialog()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::onSaveOBJDialog);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


void ProjectMainWindow::lamda_onSaveTXTDialog()
{
    QFuture<void> future = QtConcurrent::run(this, &ProjectMainWindow::onSaveTXTDialog);
    while (!future.isFinished())
    {
        QApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}


/***************************************************************
* 改写交互函数
***************************************************************/

//double* PickerInteractorStyle::lamda_generatePath(vtkPoints* p, vtkImageData* bone_IMG_Data, double screwLen, int* resolution)
//{
//    QFuture<double*> future = QtConcurrent::run(this, &PickerInteractorStyle::lamda_generatePath(p, bone_IMG_Data, screwLen, resolution));
//    while (!future.isFinished())
//    {
//        QApplication::processEvents(QEventLoop::AllEvents, 100);
//    }
//}