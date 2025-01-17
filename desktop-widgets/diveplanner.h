// SPDX-License-Identifier: GPL-2.0
#ifndef DIVEPLANNER_H
#define DIVEPLANNER_H

#include <QGraphicsPathItem>
#include <QAbstractTableModel>
#include <QAbstractButton>
#include <QDateTime>
#include <QSignalMapper>
#include <QElapsedTimer>


class QListView;
class QModelIndex;
class DivePlannerPointsModel;

class DiveHandler : public QObject, public QGraphicsEllipseItem {
	Q_OBJECT
public:
	DiveHandler();

protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
signals:
	void moved();
	void clicked();
	void released();
private:
	int parentIndex();
public
slots:
	void selfRemove();
	void changeGas();
private:
	QElapsedTimer t;
};

#include "ui_diveplanner.h"

class DivePlannerWidget : public QWidget {
	Q_OBJECT
public:
	explicit DivePlannerWidget(QWidget *parent = 0);
	void setReplanButton(bool replan);
public
slots:
	void setupStartTime(QDateTime startTime);
	void settingsChanged();
	void atmPressureChanged(const int pressure);
	void heightChanged(const int height);
	void waterTypeChanged(const int index);
	void customSalinityChanged(double density);
	void printDecoPlan();
	void setSurfacePressure(int surface_pressure);
	void setSalinity(int salinity);
private:
	Ui::DivePlanner ui;
	QAbstractButton *replanButton;
	void waterTypeUpdateTexts();
};

#include "ui_plannerSettings.h"

class PlannerSettingsWidget : public QWidget {
	Q_OBJECT
public:
	explicit PlannerSettingsWidget(QWidget *parent = 0);
	~PlannerSettingsWidget();
public
slots:
	void settingsChanged();
	void printDecoPlan();
	void setBackgasBreaks(bool dobreaks);
	void disableDecoElements(int mode);
	void disableBackgasBreaks(bool enabled);
	void setDiveMode(int mode);
	void setBailoutVisibility(int mode);

private:
	Ui::plannerSettingsWidget ui;
	void updateUnitsUI();
};

#include "ui_plannerDetails.h"

class PlannerDetails : public QWidget {
	Q_OBJECT
public:
	explicit PlannerDetails(QWidget *parent = 0);
	QPushButton *printPlan() const { return ui.printPlan; }
	QTextEdit *divePlanOutput() const { return ui.divePlanOutput; }
	QLabel *divePlannerOutputLabel() const { return ui.divePlanOutputLabel; }

private:
	Ui::plannerDetails ui;
};

#endif // DIVEPLANNER_H
