/**********************************************************************
  VibrationExtension - Visualize vibrational modes from QM calculations

  Copyright (C) 2009 by Geoffrey R. Hutchison

  This file is part of the Avogadro molecular editor project.
  For more information, see <http://avogadro.openmolecules.net/>

  Some code is based on Open Babel
  For more information, see <http://openbabel.sourceforge.net/>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation version 2 of the License.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
 ***********************************************************************/

#ifndef VIBRATIONEXTENSION_H
#define VIBRATIONEXTENSION_H

#include "vibrationdialog.h"

#include <avogadro/glwidget.h>
#include <avogadro/extension.h>

#include <QObject>
#include <QList>
#include <QString>
#include <QUndoCommand>

namespace OpenBabel {
  class OBVibrationData;
}

namespace Avogadro {

 class VibrationExtension : public Extension
  {
    Q_OBJECT

    public:
      //! Constructor
      VibrationExtension(QObject *parent=0);
      //! Deconstructor
      virtual ~VibrationExtension();

      //! \name Description methods
      //@{
      //! Plugin Name (ie Draw)
      virtual QString name() const { return QObject::tr("Vibration"); }
      //! Plugin Description (ie. Draws atoms and bonds)
      virtual QString description() const { return QObject::tr("Vibration Plugin"); };
      //! Perform Action
      virtual QList<QAction *> actions() const;
      virtual QUndoCommand* performAction(QAction *action, GLWidget *widget);
      virtual QString menuPath(QAction *action) const;

      virtual void setMolecule(Molecule *molecule);
      //@}

    public slots:
      void updateMode(int mode);

    private:
      QList<QAction *> m_actions;

      OpenBabel::OBVibrationData *m_vibrations;
      VibrationDialog *m_dialog;
      Molecule *m_molecule;
      QWidget *m_widget;
  };

  class VibrationExtensionFactory : public QObject, public PluginFactory
  {
      Q_OBJECT
      Q_INTERFACES(Avogadro::PluginFactory)

      AVOGADRO_EXTENSION_FACTORY(VibrationExtension,
          tr("Vibration Extension"),
          tr("Extension for visualizing vibrational modes from calculations."))

  };


} // end namespace Avogadro

#endif
