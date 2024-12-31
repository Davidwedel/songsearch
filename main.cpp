#include <QCoreApplication>
#include <QDirIterator>
#include <QRegularExpression>
#include <QDebug>

void searchFileNames(const QString &path, const QRegularExpression &pattern, bool recursive) {
    // Use recursive or non-recursive search
    QDirIterator::IteratorFlags flags = recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;

    // Create directory iterator
    QDirIterator it(path, QDir::Files | QDir::NoDotAndDotDot, flags);

    // Iterate through files
    while (it.hasNext()) {
        QString filePath = it.next();                 // Full file path
        QString fileName = it.fileName();             // Only file name

        if (pattern.match(fileName).hasMatch()) {     // Match file name against regex
            qWarning() << filePath;                     // Print matching file path
        }
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Command-line arguments
    QStringList args = app.arguments();

    if (args.size() < 3) {
        qCritical() << "Usage: grepfiles <pattern> <directory> [-r]";
        return 1;
    }

    // Get arguments
    QString patternStr = args[1];                     // Regular expression pattern
    QString directory = args[2];                      // Directory to search
    bool recursive = args.contains("-r");             // Recursive flag

    // Compile regex pattern
	QRegularExpression pattern(patternStr, QRegularExpression::CaseInsensitiveOption);
    if (!pattern.isValid()) {
        qCritical() << "Invalid regular expression:" << patternStr;
        return 1;
    }

    // Perform search
    searchFileNames(directory, pattern, recursive);

    return 0;
}
