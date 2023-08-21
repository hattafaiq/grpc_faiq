#ifndef TREESUBWIN_H
#define TREESUBWIN_H

#include <QTreeView>

class TreeSubwin : public QTreeView {
  Q_OBJECT
public:
  explicit TreeSubwin(QWidget *parent = nullptr);

Q_SIGNALS:
  void emitEmulateDataByClick(const QModelIndex &index);

protected:
  virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // TREESUBWIN_H
