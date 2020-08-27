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

#include "torsionextension.h"
#include "torsiondialog.h"

#include <QtGui/QAction>

#include "torsiondialog.h"

using namespace Avogadro;

namespace Torsion {

  TorsionExtension::TorsionExtension(QObject *parent)
    : Extension(parent),
      m_dialog(0),
      m_molecule(0)
  {
    // This block sets the text for menu entry
    QAction *action = new QAction(this);
    // Wrap all user visible strings in tr() so they can be translated
    action->setText(tr("0&5: Conformer Plot..."));
    m_actions.append(action);
  }

  QList<QAction *> TorsionExtension::actions() const
  {
    return m_actions;
  }

  QString TorsionExtension::menuPath(QAction *) const
  {
    return tr("E&xtensions") + '>' + tr("&Tutorial");
  }

  QUndoCommand* TorsionExtension::performAction( QAction *, GLWidget * )
  {
      QList<Primitive *> matchedPrimitives;

      OBMol *mol = new OBMol(m_molecule->OBMol());
      mol->FindTorsions();
      OBTorsionData *td = static_cast<OBTorsionData *>(mol->GetData(TorsionData));
      if (!td)
        return;
      vector<vector<unsigned int> > torsions;
      td->FillTorsionArray(torsions);
      delete mol;

      Atom *a = m_molecule->atom( torsions[rowNum][0] );
      Atom *b = m_molecule->atom( torsions[rowNum][1] );
      Atom *c = m_molecule->atom( torsions[rowNum][2] );
      Atom *d = m_molecule->atom( torsions[rowNum][3] );
      Bond *bond1 = a->bond(b);
      Bond *bond2 = b->bond(c);
      Bond *bond3 = c->bond(d);

      matchedPrimitives.append(a);
      matchedPrimitives.append(b);
      matchedPrimitives.append(c);
      matchedPrimitives.append(d);
      matchedPrimitives.append(bond1);
      matchedPrimitives.append(bond2);
      matchedPrimitives.append(bond3);

      m_widget->clearSelected();
      m_widget->setSelected(matchedPrimitives, true);
      m_widget->update();

      QUndoCommand *undo = 0;
      PropertiesModel *model;
      PropertiesView  *view;
      QDialog *dialog = new QDialog(qobject_cast<QWidget *>(parent()));
      QVBoxLayout *layout = new QVBoxLayout(dialog);
      dialog->setLayout(layout);
      // Don't show whitespace around the PropertiesView
      layout->setSpacing(0);
      layout->setContentsMargins(0,0,0,0);


      // model will be deleted in PropertiesView::hideEvent using deleteLater().
      model = new PropertiesModel(PropertiesModel::TorsionType);
      model->setMolecule( m_molecule );
      // view will delete itself in PropertiesView::hideEvent using deleteLater().
      view = new PropertiesView(PropertiesView::TorsionType, widget);


      connect(m_molecule, SIGNAL(moleculeChanged()), model, SLOT(moleculeChanged()));
      connect(m_molecule, SIGNAL( updated() ), model, SLOT( updateTable() ));

      QSortFilterProxyModel* proxyModel = new QSortFilterProxyModel(this);
      proxyModel->setSourceModel(model);
      proxyModel->setDynamicSortFilter(true);
      proxyModel->setSortLocaleAware(true);
      // this role will received direct floating-point numbers from the model
      proxyModel->setSortRole(Qt::UserRole);

      view->setMolecule( m_molecule );
      view->setWidget( widget );
      view->setModel( proxyModel );
      view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
      view->resizeColumnsToContents();
      layout->addWidget(view);
      dialog->setWindowTitle(view->windowTitle());
      QSize dialogSize = dialog->size();
      double width = view->horizontalHeader()->length()+view->verticalHeader()->width()+5;
      if (model->rowCount() < 13) { // no scrollbar
        dialogSize.setHeight(view->horizontalHeader()->height()+model->rowCount()*30+5);
        dialogSize.setWidth(width);
      } else { // scrollbar is needed
        dialogSize.setHeight(width/1.618);
        dialogSize.setWidth(width+view->verticalScrollBar()->width());
      }
      dialog->resize(dialogSize);
      //dialog->setWindowFlags(Qt::Window);
      dialog->show();

      return undo;
  }

  void TorsionExtension::setMolecule(Molecule *mol)
  {
    m_molecule = mol;

    if (m_dialog) {
      m_dialog->refresh(m_molecule);
    }
  }

}

// Include Qt moc'd headers
#include "torsionextension.moc"

// Set up for the plugin to work correctly
Q_EXPORT_PLUGIN2(torsionextension, Torsion::TorsionExtensionFactory)
