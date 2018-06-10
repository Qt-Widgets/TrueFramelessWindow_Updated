#include "widget.h"

#include <QApplication>
#include <QLabel>
#include <QLayout>
#include <QMenuBar>
#include <QStyle>
#include <QUrl>

#include "thememanager.h"

Widget::Widget(QWidget* parent) : QMainWindow(parent) {
  window_title_ = "Test Window";  // move to qwinwidget maybe?

  Theme theme = ThemeManager::SharedManager().theme();

  QPalette Pal(palette());
  Pal.setColor(QPalette::Background, theme["background"]);
  setAutoFillBackground(true);
  setPalette(Pal);

  // Windows example of adding a toolbar + min/max/close buttons
#ifdef _WIN32

  // Add the toolbar
  toolBar = new QToolBar(this);
  toolBar->setMovable(false);
  toolBar->setFloatable(false);
  toolBar->setStyleSheet("background-color: none; border: none;");
  addToolBar(toolBar);

  // Create a transparent-to-mouse-events widget that pads right for a fixed
  // width equivalent to min/max/close buttons
  QWidget* btnSpacer = new QWidget(toolBar);
  btnSpacer->setAttribute(Qt::WA_TransparentForMouseEvents);
  btnSpacer->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  btnSpacer->setStyleSheet("background-color: none; border: none;");
  btnSpacer->setFixedWidth(135 /* rough width of close/min/max buttons */);
  // toolBar->addWidget(btnSpacer);

  // Create a title label just because
  QLabel* titleLabel = new QLabel(window_title_);
  titleLabel->setFixedWidth(160);
  titleLabel->setStyleSheet(QString("color:%1;").arg(theme["text"].name()));
  // titleLabel->setAlignment(Qt::AlignHCenter);
  // Set it transparent to mouse events such that you can click and drag when
  // moused over the label
  titleLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

  // Create spacer widgets to keep the title centered
  QWidget* leftSpacer = new QWidget(toolBar);
  QWidget* rightSpacer = new QWidget(toolBar);

  // Set them transparent to mouse events + auto-expanding in size
  leftSpacer->setAttribute(Qt::WA_TransparentForMouseEvents);
  leftSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  leftSpacer->setStyleSheet("background-color: none; border: none;");
  rightSpacer->setAttribute(Qt::WA_TransparentForMouseEvents);
  rightSpacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  rightSpacer->setStyleSheet("background-color: none; border: none;");

  QLabel* app_icon_label = new QLabel();
  //  app_icon_label->setPixmap(app_icon.pixmap(QSize(18, 18)));
  //  app_icon_label->setMargin(0);
  //  app_icon_label->setContentsMargins(4, 2, 4, 2);

  toolBar->addWidget(app_icon_label);
  toolBar->addWidget(titleLabel);
  toolBar->addWidget(rightSpacer);

  QIcon close_icon = QIcon(QStringLiteral(":/res/close.svg"));
  QIcon max_icon = QIcon(QStringLiteral(":/res/maximize.svg"));
  QIcon min_icon = QIcon(QStringLiteral(":/res/minimize.svg"));
  // Create the min/max/close buttons
  minimizeButton = new QPushButton();
  maximizeButton = new QPushButton();
  closeButton = new QPushButton();

  minimizeButton->setIcon(min_icon);
  maximizeButton->setIcon(max_icon);
  closeButton->setIcon(close_icon);
  minimizeButton->setIconSize(QSize(12, 12));
  maximizeButton->setIconSize(QSize(12, 12));
  closeButton->setIconSize(QSize(12, 12));

  minimizeButton->setStyleSheet(
      "QPushButton{background: transparent; border-radius:0;}");
  maximizeButton->setStyleSheet(
      "QPushButton{background: transparent; border-radius:0;}");
  closeButton->setStyleSheet(
      "QPushButton{background: transparent; border-radius:0;}");

  maximizeButton->setCheckable(true);

  minimizeButton->setMinimumSize(45, 22);
  maximizeButton->setMinimumSize(45, 22);
  closeButton->setMinimumSize(45, 22);

  toolBar->addWidget(minimizeButton);
  toolBar->addWidget(maximizeButton);
  toolBar->addWidget(closeButton);
  toolBar->layout()->setAlignment(minimizeButton, Qt::AlignTop);
  toolBar->layout()->setAlignment(maximizeButton, Qt::AlignTop);
  toolBar->layout()->setAlignment(closeButton, Qt::AlignTop);

  // toolBar->layout()->setMenuBar(menuBar);

  addToolBarBreak();

  // An actual app should use icons for the buttons instead of text
  // and style the different button states / widget margins in css

#endif

  QToolBar* menuToolbar = new QToolBar();
  menuToolbar->setMovable(false);
  menuToolbar->setFloatable(false);
  menuToolbar->setStyleSheet("background-color: none; border: none;");

  QMenuBar* menuBar = new QMenuBar();
  menuBar->setStyleSheet(QString("color:%1;").arg(theme["text"].name()));
  QMenu* fileMenu = new QMenu("File");
  menuBar->addMenu(fileMenu);
  QMenu* cpuMenu = new QMenu("CPU");
  menuBar->addMenu(cpuMenu);
  QMenu* gpuMenu = new QMenu("GPU");
  menuBar->addMenu(gpuMenu);
  QMenu* windowMenu = new QMenu("Window");
  menuBar->addMenu(windowMenu);
  QMenu* helpMenu = new QMenu("Help");
  menuBar->addMenu(helpMenu);
  fileMenu->addAction("Save");
  fileMenu->addAction("Exit");

  menuToolbar->layout()->setMenuBar(menuBar);
  addToolBar(menuToolbar);
}

void Widget::paintEvent(QPaintEvent* event) {
  //  QPainter painter(this);
  //  QImage backgroundImage(QStringLiteral(":/res/background.png"));
  //  painter.drawImage(contentsRect(), backgroundImage);
}

QString Widget::window_title() const { return window_title_; }
