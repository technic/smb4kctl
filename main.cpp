// qt
#include <QDebug>
// KDE
#include <KApplication>
#include <KAboutData>
#include <KCmdLineArgs>
#include <KUrl>
// my
#include "smb4kctl.h"

int main(int argc, char** argv)
{
    KAboutData aboutData
    (   "smb4kctl", "",
        ki18n("smb4kctl"), "0.1",
        ki18n("Mount samba shares using smb4k library"),
        KAboutData::License_GPL,
        ki18n("Copyright (c) 2015 Alex Maystrenko <alexeytech@gmail.com")
    );
    KCmdLineArgs::init(argc, argv, &aboutData);

    KCmdLineOptions options;
    options.add("+cmd", ki18n("mount or umount"));
    options.add("+url", ki18n("samba url for exmaple smb://server/share"));
    KCmdLineArgs::addCmdLineOptions(options);

    KApplication app;
    KCmdLineArgs *args = KCmdLineArgs::parsedArgs();

    if(args->count() != 2)
    {
        args->usage();
        return 1;
    }
	
    int cmd;
    if(args->arg(0) == "mount")
	{
		cmd = CMD_mount;
    } 
    else if(args->arg(0) == "umount") 
	{
        cmd = CMD_umount;
    }
	else {
		qDebug() << "1";
		args->usage();
		return 1;
	}
    Smb4KCtl mount_main(cmd, args->url(1));

    return app.exec();
}
