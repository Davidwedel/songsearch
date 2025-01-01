#include <QCoreApplication>
#include <QDirIterator>
#include <QRegularExpression>
#include <QDebug>
#include <QProcess>
#include <iostream>


void searchFileNames(const QString &path, const QRegularExpression &pattern, QStringList &fileList) {

    // Create directory iterator
    QDirIterator it(path, QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
	uint number = 1;

    // Iterate through files
    while (it.hasNext()) {
        QString filePath = it.next();                 // Full file path
        QString fileName = it.fileName();             // Only file name

        if (pattern.match(fileName).hasMatch()) {     // Match file name against regex
            qWarning() << number << filePath;                     // Print matching file path
            fileList.append(filePath);
			number++;
        }
    }
}

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    // Command-line arguments
    QStringList args = app.arguments();

    if (args.size() < 1) {
        qCritical() << "Usage: fs <pattern>";
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
    QStringList fileList;
    searchFileNames(directory, pattern, fileList); // Check if any files were found

        if (fileList.isEmpty()) {
        qWarning() << "No matching files found.";
        return 0;
    }

    // Prompt user for input
    qInfo() << "Enter a number (1 -" << fileList.size() << ") to open a file, or 0 to exit:";

    int choice = 0;
    std::cin >> choice;

    if (choice > 0 && choice <= fileList.size()) {
        // Open the selected file
        QString fileToOpen = fileList[choice - 1];
        qInfo() << "Opening file:" << fileToOpen;

        // Extract the file extension
        QString extension = fileToOpen.section('.', -1).toLower(); // Get text after the last '.'
        qDebug() << extension;

        // Check if the extension is 'pptx'
        if (extension == "pptx") {
            // Open with LibreOffice
            QProcess::startDetached("libreoffice", QStringList() << fileToOpen);
        } else {
            // Open with the default application
            QProcess::startDetached("xdg-open", QStringList() << fileToOpen);
        }    } else if (choice != 0) {
        qWarning() << "Invalid selection.";
    }

    return 0;
}
