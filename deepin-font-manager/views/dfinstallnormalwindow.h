#ifndef DFINSTALLNORMALWINDOW_H
#define DFINSTALLNORMALWINDOW_H

#include "dfontbasedialog.h"
#include "dfmdbmanager.h"
#include "dfinstallerrordialog.h"
#include "dfontinfomanager.h"
#include "signalmanager.h"

#include <QStringList>
#include <QTimer>

#include <DDialog>
#include <DFrame>
#include <DLabel>
#include <DProgressBar>
#include <DMessageManager>

DWIDGET_USE_NAMESPACE

class DFontManager;
class DFontInfoManager;
class DFInstallErrorDialog;

class DFInstallNormalWindow : public DFontBaseDialog
{
    Q_OBJECT
public:
    DFInstallNormalWindow(const QStringList &files = QStringList(), QWidget *parent = nullptr);
    ~DFInstallNormalWindow() override;

    void setSkipException(bool skip);
    void breakInstalltion();

protected:
    static constexpr int VERIFY_DELYAY_TIME = 1000;

    void initUI();
    void initConnections();
    void GetAllSysfiles();
    void initVerifyTimer();

    void verifyFontFiles();
    bool ifNeedShowExceptionWindow() const;
    bool isSystemFont(DFontInfo &f);
    void checkShowMessage();

    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;
protected slots:
    void batchInstall();
    void batchReInstall();
    void onProgressChanged(const QString &filePath, const double &percent);

    void onCancelInstall();
    void onContinueInstall(const QStringList &continueInstallFontFileList);

    void showInstallErrDlg();

signals:
    void batchReinstall(const QStringList &reinstallFiles);
    void finishFontInstall(const QStringList &fileList);
    void addFont(const QStringList &fileList);


private:
    enum InstallState { Install, reinstall, damaged };

    QStringList m_installFiles;
    QStringList m_installedFiles;
    QStringList m_newInstallFiles;
    QStringList m_damagedFiles;
    QStringList m_systemFiles;
    QStringList m_outfileList;
    QStringList m_errorList;
    QStringList m_AllSysFiles;


    int totalInstallFont = 0;
    int totalSysFontCount = 0;
    bool getInstallMessage = false;
    bool getReInstallMessage = false;

    // Skip popup exception dialog if true
    bool m_isNeedSkipException {false};
    bool m_isFristThreadEnd = false;
    int systemFontCount = 0;

    InstallState m_installState {Install};

    QList<DFInstallErrorItemModel *> m_installErrorFontModelList;
    DFontInfoManager *m_fontInfoManager;
    DFontManager *m_fontManager;
    SignalManager *m_signalManager = SignalManager::instance();

    DLabel *m_logoLabel {nullptr};
    DLabel *m_titleLabel {nullptr};
    QWidget *m_titleFrame {nullptr};
    QWidget *m_mainFrame {nullptr};

    DLabel *m_progressStepLabel {nullptr};
    DLabel *m_currentFontLabel {nullptr};
    DProgressBar *m_progressBar {nullptr};

    DFInstallErrorDialog *m_pexceptionDlg {nullptr};
    void keyPressEvent(QKeyEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
    QScopedPointer<QTimer> m_verifyTimer {nullptr};
};

#endif  // DFINSTALLNORMALWINDOW_H
