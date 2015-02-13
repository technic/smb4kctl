#include <QCoreApplication>

#include "smb4kctl.h"
#include <smb4ksettings.h>

Smb4KCtl::Smb4KCtl(int cmd, KUrl url): m_cmd(cmd)
{
    connect( Smb4KMounter::self(), SIGNAL(mounted(Smb4KShare*)),
             this,                 SLOT(slotMounted(Smb4KShare*)) );

    connect( Smb4KMounter::self(), SIGNAL(unmounted(Smb4KShare*)),
             this,                 SLOT(slotUmounted(Smb4KShare*)) );

    connect( Smb4KMounter::self(), SIGNAL(finished(Smb4KShare*,int)),
             this,                 SLOT(slotFinished(Smb4KShare*,int)) );

    share.setURL(url);

	//FIXME copypaste from smb4mounter
    QString mountpoint;
    mountpoint += Smb4KSettings::mountPrefix().path();
    mountpoint += QDir::separator();
    mountpoint += (Smb4KSettings::forceLowerCaseSubdirs() ? share.hostName().toLower() : share.hostName());
    mountpoint += QDir::separator();
    mountpoint += (Smb4KSettings::forceLowerCaseSubdirs() ? share.shareName().toLower() : share.shareName());
	//
	
    if (cmd == CMD_mount) {
        qDebug() << "Start mount share" << share.url();
        Smb4KMounter::self()->mountShare(&share);
    }
    if (cmd == CMD_umount) {
        share.setPath(mountpoint);
        qDebug() << "Start umount share" << share.canonicalPath();
        Smb4KMounter::self()->unmountShare(&share);
    }
}

Smb4KCtl::~Smb4KCtl()
{}

void Smb4KCtl::slotMounted(Smb4KShare *share)
{
    qDebug() << "mounted" << share->url().pathOrUrl();
}

void Smb4KCtl::slotUmounted(Smb4KShare *share)
{
    qDebug() << "umounted" << share->canonicalPath();
}

void Smb4KCtl::slotFinished(Smb4KShare *share, int process)
{
    if(m_cmd == CMD_mount && !share->isMounted())
    {
        qDebug() << "failed to mount" << share->url().pathOrUrl();
    }
    if(m_cmd == CMD_umount && share->isMounted())
    {
        qDebug() << "failed to umount" << share->url().pathOrUrl();
    }
    if(m_cmd == CMD_umount && !share->isMounted())
    {
        qDebug() << "unmounted" << share->url().pathOrUrl();
    }

    qDebug() << "finished";
    QCoreApplication::exit(0);
}

#include "smb4kctl.moc"
