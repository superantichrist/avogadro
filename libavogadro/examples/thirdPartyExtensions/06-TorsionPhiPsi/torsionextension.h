/**********************************************************************
  TorsionExtension

  Copyright (C) 2010 David C. Lonie

  This file is part of the Avogadro molecular editor project.
  For more information, see <http://avogadro.cc/>

  Avogadro is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  Avogadro is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
  02110-1301, USA.
 **********************************************************************/

#ifndef TORSIONEXTENSION_H
#define TORSIONEXTENSION_H

#include "propmodel.h"

#include <avogadro/global.h>
#include <avogadro/plugin.h>
#include <avogadro/extension.h>


// This is a work around for a bug on older versions Avogadro, bug
// 3104853. Patch submitted.
using Avogadro::Plugin;

namespace Torsion {
  // Forward declaration of header
  class TorsionDialog;

  class Molecule;
  class PropertiesView;

  class TorsionExtension : public Avogadro::Extension
  {
    Q_OBJECT
    AVOGADRO_EXTENSION("Conformer Plot Extension",
                       tr("Plot conformer energies"),
                       tr("Plot the energies of a molecule's conformers."))

  public:
    TorsionExtension(QObject *parent=0);
    ~TorsionExtension() {};

    // This tells Avogadro what actions to create
    virtual QList<QAction *> actions() const;
    // This returns a string that tells Avogadro where to put the menu entries
    virtual QString menuPath(QAction *action) const;
    // When an action is requested (e.g. a user selects a menu entry),
    // here is where it is handled:
    virtual QUndoCommand* performAction(QAction *action,
                                        Avogadro::GLWidget *widget);
    // This is called whenever a new molecule is loaded. This is not
    // needed for this extension.
    virtual void setMolecule(Avogadro::Molecule *molecule);

  private:
    QList<QAction *> m_actions;
    TorsionDialog *m_dialog;
    Avogadro::Molecule *m_molecule;
  };

  class PropertiesView : public QTableView
  {
    Q_OBJECT

     public:
       enum Type {
         OtherType=0,
         AtomType,
         BondType,
         AngleType,
         TorsionType,
         //CartesianType,
         ConformerType,
         MoleculeType
       };

       explicit PropertiesView(Type type, QWidget *parent = 0);

       void selectionChanged(const QItemSelection &selected,
                             const QItemSelection &previous);
       void setMolecule (Molecule *molecule);
       void setWidget (GLWidget *widget);
       void hideEvent(QHideEvent *event);

     private:
       int m_type;
       Molecule *m_molecule;
       GLWidget *m_widget;
  };

  // Plugin factory setup
  class TorsionExtensionFactory
    : public QObject,
      public Avogadro::PluginFactory
  {
    Q_OBJECT
    Q_INTERFACES(Avogadro::PluginFactory)
    AVOGADRO_EXTENSION_FACTORY(TorsionExtension)
  };

}

#endif

