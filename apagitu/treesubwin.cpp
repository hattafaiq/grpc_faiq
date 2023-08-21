#include "treesubwin.h"
#include <QKeyEvent>
#include <QtDebug>

TreeSubwin::TreeSubwin(QWidget *parent) : QTreeView(parent)
{
    setSelectionMode(QTreeView::SingleSelection);
    setSelectionBehavior(QTreeView::SelectRows);
}

void expandChildren(const QModelIndex &index, QTreeView *view) {
  if (!index.isValid()) {
    return;
  }

  int childCount = index.model()->rowCount(index);
  for (int i = 0; i < childCount; i++) {
    const QModelIndex &child = index.child(i, 0);
    expandChildren(child, view);
  }

  view->expand(index);
}

void TreeSubwin::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Up) {
    auto modelsel = selectionModel();
    QModelIndex index = currentIndex();
    auto ch_model = index.model();
    if (modelsel && ch_model) {
      QModelIndex newidx = index.siblingAtRow(index.row() - 1);
      if (newidx.row() < 0) {
        newidx = index.parent();
        if (!newidx.isValid()) {
          event->accept();
          return;
        }
      }

      setCurrentIndex(newidx);
      modelsel->select(newidx, QItemSelectionModel::ClearAndSelect |
                                   QItemSelectionModel::Rows);
      // emitEmulateDataByClick(newidx);
      event->accept();
    }
  }
  if (event->key() == Qt::Key_Down) {
    auto modelsel = selectionModel();
    QModelIndex index = currentIndex();
    auto ch_model = index.model();
    if (modelsel && ch_model) {
      int ch_count = ch_model->rowCount(index);
      QModelIndex newidx;
      if (ch_count > 0) {
        newidx = ch_model->index(0, 0, index);
      } else {
        int rowcnt = ch_model->rowCount();
        if (index.row() + 1 >= rowcnt) {
          newidx = index.parent();

          auto to_idx = newidx.siblingAtRow(newidx.row() + 1);
          if (to_idx.row() < 0) {
            newidx = newidx.parent();
          } else {
            newidx = to_idx;
          }
        } else {
          newidx = index.siblingAtRow(index.row() + 1);
        }
      }
      setCurrentIndex(newidx);
      modelsel->select(newidx, QItemSelectionModel::ClearAndSelect |
                                   QItemSelectionModel::Rows);
      // emitEmulateDataByClick(newidx);
      event->accept();
    }
  }
  if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Space) {
    QModelIndex index = currentIndex();
    auto ch_model = index.model();
    if (index.isValid() && ch_model) {
      int ch_count = ch_model->rowCount(index);
      if (ch_count > 0) {
        expandChildren(index, this);
      } else {
        emitEmulateDataByClick(index);
      }
      event->accept();
    }
  }
}

