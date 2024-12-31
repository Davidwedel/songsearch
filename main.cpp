#include <QCoreApplication>
#include <QDirIterator>
#include <QRegularExpression>
#include <QDebug>

void searchFileNames(const QString &path, const QRegularExpression &pattern) {

    // Create directory iterator
    QDirIterator it(path, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);

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

    if (args.size() < 1) {
        qCritical() << "Usage: filesearch <pattern>";
        return 1;
    }

    // Get arguments
    QString patternStr = args[1];                     // Regular expression pattern
    QString directory = ".";                      // Directory to search

    // Compile regex pattern
	QRegularExpression pattern(patternStr, QRegularExpression::CaseInsensitiveOption);
    if (!pattern.isValid()) {
        qCritical() << "Invalid regular expression:" << patternStr;
        return 1;
    }

    // Perform search
    searchFileNames(directory, pattern);

    return 0;
}
