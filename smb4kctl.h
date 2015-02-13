#ifndef smb4k_mount_H
#define smb4k_mount_H

#include <QtCore/QObject>
#include <QDebug>

#include <smb4kmounter.h>
#include <smb4kshare.h>

enum {CMD_mount, CMD_umount};
int smb4k_main(int argc, char** argv, int cmd);

class Smb4KCtl : public QObject
{
    Q_OBJECT

    Smb4KShare share;
    int m_cmd;

public:
    Smb4KCtl(int cmd, KUrl url);
    ~Smb4KCtl();

private slots:
	void slotMounted(Smb4KShare *share);
	void slotFinished(Smb4KShare *share, int process);
    void slotUmounted(Smb4KShare* share);
};

#endif // smb4k_mount_H
