#include "app_command.h"

BaseAppCommand::~BaseAppCommand() {}

void LaunchAppCmd::execute()
{
    std::unique_ptr<QProcess> process;
    process = std::unique_ptr<QProcess>(new QProcess());

    QString program = "/home/lev/Рабочий стол/study/semester_5/bmstu_cg_course_project/build-cg_course-Desktop-Release/bmstu_cg_course_project";

    process->startDetached(program, QStringList() << "");
    process->waitForFinished(-1);
}
