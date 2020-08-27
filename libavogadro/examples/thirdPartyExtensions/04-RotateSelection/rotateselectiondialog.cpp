/**********************************************************************
  RotateSelectionExtension

  Copyright (C) 2010 David C. Lonie

  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Library General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 ***********************************************************************/

//#include "config.h"

#include "rotateselectiondialog.h"

#include <Eigen/Core>

namespace RotateSelection {

  RotateSelectionDialog::RotateSelectionDialog(QWidget *parent, Qt::WindowFlags f ) :
    QDialog( parent, f )
  {
    ui.setupUi(this);

    connect(ui.push_useBond, SIGNAL(clicked()),
            this, SIGNAL(requestUpdateAxisFromBond()));
    connect(ui.push_apply, SIGNAL(clicked()),
            this, SIGNAL(requestApply()));
  }

  void RotateSelectionDialog::getTransform(Eigen::Vector3d *axis,
                                           Eigen::Vector3d *offset,
                                           double *angle)
  {
    *axis = Eigen::Vector3d(ui.spin_vx->value(),
                            ui.spin_vy->value(),
                            ui.spin_vz->value());
    *offset = Eigen::Vector3d(ui.spin_tx->value(),
                              ui.spin_ty->value(),
                              ui.spin_tz->value());
    *angle = ui.spin_angle->value();
  }

  void RotateSelectionDialog::setAxis(const Eigen::Vector3d &axis,
                                      const Eigen::Vector3d &offset)
  {
    ui.spin_vx->setValue(axis.x());
    ui.spin_vy->setValue(axis.y());
    ui.spin_vz->setValue(axis.z());
    ui.spin_tx->setValue(offset.x());
    ui.spin_ty->setValue(offset.y());
    ui.spin_tz->setValue(offset.z());
  }


}

// This includes the files generated by Qt's moc at compile time to
// ensure that signals/slots work. If you ever see errors about
// missing vtables with gcc, check that you haven't forgotten one of
// these:
#include "rotateselectiondialog.moc"
