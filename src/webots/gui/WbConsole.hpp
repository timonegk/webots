// Copyright 1996-2020 Cyberbotics Ltd.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef WB_CONSOLE_HPP
#define WB_CONSOLE_HPP

//
// Description: Webots console widget
//

#include "WbActionManager.hpp"
#include "WbDockWidget.hpp"
#include "WbLog.hpp"

class QAction;
class QComboBox;
class QPushButton;
class QRegExp;
class WbFindReplaceDialog;
class WbTextFind;
class ConsoleEdit;

class WbConsole : public WbDockWidget {
  Q_OBJECT
  // WbLog colors
  Q_PROPERTY(QString errorColor MEMBER mErrorColor READ errorColor WRITE setErrorColor)
  Q_PROPERTY(QString infoColor MEMBER mInfoColor READ infoColor WRITE setInfoColor)
  // ANSI escape code colors
  Q_PROPERTY(QString ansiBlack MEMBER mAnsiBlack READ ansiBlack WRITE setAnsiBlack)
  Q_PROPERTY(QString ansiRed MEMBER mAnsiRed READ ansiRed WRITE setAnsiRed)
  Q_PROPERTY(QString ansiGreen MEMBER mAnsiGreen READ ansiGreen WRITE setAnsiGreen)
  Q_PROPERTY(QString ansiYellow MEMBER mAnsiYellow READ ansiYellow WRITE setAnsiYellow)
  Q_PROPERTY(QString ansiBlue MEMBER mAnsiBlue READ ansiBlue WRITE setAnsiBlue)
  Q_PROPERTY(QString ansiMagenta MEMBER mAnsiMagenta READ ansiMagenta WRITE setAnsiMagenta)
  Q_PROPERTY(QString ansiCyan MEMBER mAnsiCyan READ ansiCyan WRITE setAnsiCyan)
  Q_PROPERTY(QString ansiWhite MEMBER mAnsiWhite READ ansiWhite WRITE setAnsiWhite)

public:
  // singleton
  static WbConsole *instance();

  explicit WbConsole(QWidget *parent = NULL, const QString &name = QString("Console"));
  virtual ~WbConsole();

  // parse compilation error line
  void jumpToError(const QString &errorLine);

  // console clear action to be used in menus

  // enable redirecting messages to the terminal
  static void enableStdOutRedirectToTerminal();
  static void enableStdErrRedirectToTerminal();

  const QString &errorColor() const { return mErrorColor; }
  const QString &infoColor() const { return mInfoColor; }

  const QString &ansiBlack() const { return mAnsiBlack; }
  const QString &ansiRed() const { return mAnsiRed; }
  const QString &ansiGreen() const { return mAnsiGreen; }
  const QString &ansiYellow() const { return mAnsiYellow; }
  const QString &ansiBlue() const { return mAnsiBlue; }
  const QString &ansiMagenta() const { return mAnsiMagenta; }
  const QString &ansiCyan() const { return mAnsiCyan; }
  const QString &ansiWhite() const { return mAnsiWhite; }

  void setErrorColor(const QString &color) { mErrorColor = color; }
  void setInfoColor(const QString &color) { mInfoColor = color; }

  void setAnsiBlack(const QString &color) { mAnsiBlack = color; }
  void setAnsiRed(const QString &color) { mAnsiRed = color; }
  void setAnsiGreen(const QString &color) { mAnsiGreen = color; }
  void setAnsiYellow(const QString &color) { mAnsiYellow = color; }
  void setAnsiBlue(const QString &color) { mAnsiBlue = color; }
  void setAnsiMagenta(const QString &color) { mAnsiMagenta = color; }
  void setAnsiCyan(const QString &color) { mAnsiCyan = color; }
  void setAnsiWhite(const QString &color) { mAnsiWhite = color; }

  const QStringList getEnabledLogs() const { return mEnabledLogs; }
  void setEnabledLogs(const QStringList &logs);

signals:
  void closed();

public slots:
  // clear console and resets its attributes when performed by webots
  // only from within a controller, this option is set to false
  void clear(bool reset = true);

  // append internal error message of Webots
  // the message color depends on the level
  void appendLog(WbLog::Level level, const QString &message, bool popup, const QString &robotName);  // TODO: rename in logName?

private:
  QString mErrorColor, mInfoColor;
  QString mAnsiBlack, mAnsiRed, mAnsiGreen, mAnsiYellow, mAnsiBlue, mAnsiMagenta, mAnsiCyan, mAnsiWhite;
  QStringList mEnabledLogs;
  ConsoleEdit *mEditor;
  QPushButton *mFiltersButton;
  QRegExp **mErrorPatterns;
  QString mForegroundColor;
  QString mBackgroundColor;
  bool mBold;
  bool mUnderline;
  bool mIsOverwriteEnabled;

  void resetFormat();
  QString htmlSpan(const QString &s, WbLog::Level level) const;
  void handleCRAndLF(const QString &msg);
  void handlePossibleAnsiEscapeSequences(const QString &msg, WbLog::Level);
  QRegExp **createErrorMatchingPatterns() const;
  void updateTitle();

  void openFindDialog();
  WbFindReplaceDialog *mFindDialog;
  WbTextFind *mTextFind;

protected slots:
  void closeEvent(QCloseEvent *event) override;

private slots:
  void selectFilters();
  void updateFont();
  void enableCopyAction(bool enabled);
  void handleUserCommand(WbActionManager::WbActionKind actionKind);
  void deleteFindDialog();
};

#endif
