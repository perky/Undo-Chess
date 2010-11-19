/*
 * Internal function/structure declaration. Do NOT include in your
 *  application.
 *
 * Please see the file LICENSE.txt in the source's root directory.
 *
 *  This file written by Ryan C. Gordon.
 */

#ifndef _INCLUDE_PHYSFS_INTERNAL_H_
#define _INCLUDE_PHYSFS_INTERNAL_H_

#ifndef __PHYSICSFS_INTERNAL__
#error Do not include this header from your applications.
#endif

#include "physfs.h"

#include <stdlib.h>  /* make sure NULL is defined... */

#ifdef HAVE_ASSERT_H
#include <assert.h>
#elif (!defined assert)
#define assert(x)
#endif

/* !!! FIXME: remove this when revamping stack allocation code... */
#ifdef _MSC_VER
#include <malloc.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Interface for small allocations. If you need a little scratch space for
 *  a throwaway buffer or string, use this. It will make small allocations
 *  on the stack if possible, and use allocator.Malloc() if they are too
 *  large. This helps reduce malloc pressure.
 * There are some rules, though:
 * NEVER return a pointer from this, as stack-allocated buffers go away
 *  when your function returns.
 * NEVER allocate in a loop, as stack-allocated pointers will pile up. Call
 *  a function that uses smallAlloc from your loop, so the allocation can
 *  free each time.
 * NEVER call smallAlloc with any complex expression (it's a macro that WILL
 *  have side effects...it references the argument multiple times). Use a
 *  variable or a literal.
 * NEVER free a pointer from this with anything but smallFree. It will not
 *  be a valid pointer to the allocator, regardless of where the memory came
 *  from.
 * NEVER realloc a pointer from this.
 * NEVER forget to use smallFree: it may not be a pointer from the stack.
 * NEVER forget to check for NULL...allocation can fail here, of course!
 */
#define __PHYSFS_SMALLALLOCTHRESHOLD 128
void *__PHYSFS_initSmallAlloc(void *ptr, PHYSFS_uint64 len);

#define __PHYSFS_smallAlloc(bytes) ( \
    __PHYSFS_initSmallAlloc((((bytes) < __PHYSFS_SMALLALLOCTHRESHOLD) ? \
                             alloca((size_t)((bytes)+1)) : NULL), (bytes)) \
)

void __PHYSFS_smallFree(void *ptr);


/* Use the allocation hooks. */
#define malloc(x) Do not use malloc() directly.
#define realloc(x, y) Do not use realloc() directly.
#define free(x) Do not use free() directly.
/* !!! FIXME: add alloca check here. */

/* The LANG section. */
/*  please send questions/translations to Ryan: icculus@icculus.org. */

#if (!defined PHYSFS_LANG)
#  define PHYSFS_LANG PHYSFS_LANG_ENGLISH
#endif

#define PHYSFS_LANG_ENGLISH            1  /* English by Ryan C. Gordon  */
#define PHYSFS_LANG_RUSSIAN_KOI8_R     2  /* Russian by Ed Sinjiashvili */
#define PHYSFS_LANG_RUSSIAN_CP1251     3  /* Russian by Ed Sinjiashvili */
#define PHYSFS_LANG_RUSSIAN_CP866      4  /* Russian by Ed Sinjiashvili */
#define PHYSFS_LANG_RUSSIAN_ISO_8859_5 5  /* Russian by Ed Sinjiashvili */
#define PHYSFS_LANG_SPANISH            6  /* Spanish by Pedro J. P�rez  */
#define PHYSFS_LANG_FRENCH             7  /*  French by St�phane Peter  */
#define PHYSFS_LANG_GERMAN             8  /*  German by Michael Renner  */
#define PHYSFS_LANG_PORTUGUESE_BR      9  /* pt-br by Danny Angelo Carminati Grein  */

#if (PHYSFS_LANG == PHYSFS_LANG_ENGLISH)
 #define DIR_ARCHIVE_DESCRIPTION  "Non-archive, direct filesystem I/O"
 #define GRP_ARCHIVE_DESCRIPTION  "Build engine Groupfile format"
 #define HOG_ARCHIVE_DESCRIPTION  "Descent I/II HOG file format"
 #define MVL_ARCHIVE_DESCRIPTION  "Descent II Movielib format"
 #define QPAK_ARCHIVE_DESCRIPTION "Quake I/II format"
 #define ZIP_ARCHIVE_DESCRIPTION  "PkZip/WinZip/Info-Zip compatible"
 #define WAD_ARCHIVE_DESCRIPTION  "DOOM engine format"
 #define LZMA_ARCHIVE_DESCRIPTION "LZMA (7zip) format"

 #define ERR_IS_INITIALIZED       "Already initialized"
 #define ERR_NOT_INITIALIZED      "Not initialized"
 #define ERR_INVALID_ARGUMENT     "Invalid argument"
 #define ERR_FILES_STILL_OPEN     "Files still open"
 #define ERR_NO_DIR_CREATE        "Failed to create directories"
 #define ERR_OUT_OF_MEMORY        "Out of memory"
 #define ERR_NOT_IN_SEARCH_PATH   "No such entry in search path"
 #define ERR_NOT_SUPPORTED        "Operation not supported"
 #define ERR_UNSUPPORTED_ARCHIVE  "Archive type unsupported"
 #define ERR_NOT_A_HANDLE         "Not a file handle"
 #define ERR_INSECURE_FNAME       "Insecure filename"
 #define ERR_SYMLINK_DISALLOWED   "Symbolic links are disabled"
 #define ERR_NO_WRITE_DIR         "Write directory is not set"
 #define ERR_NO_SUCH_FILE         "File not found"
 #define ERR_NO_SUCH_PATH         "Path not found"
 #define ERR_NO_SUCH_VOLUME       "Volume not found"
 #define ERR_PAST_EOF             "Past end of file"
 #define ERR_ARC_IS_READ_ONLY     "Archive is read-only"
 #define ERR_IO_ERROR             "I/O error"
 #define ERR_CANT_SET_WRITE_DIR   "Can't set write directory"
 #define ERR_SYMLINK_LOOP         "Infinite symbolic link loop"
 #define ERR_COMPRESSION          "(De)compression error"
 #define ERR_NOT_IMPLEMENTED      "Not implemented"
 #define ERR_OS_ERROR             "Operating system reported error"
 #define ERR_FILE_EXISTS          "File already exists"
 #define ERR_NOT_A_FILE           "Not a file"
 #define ERR_NOT_A_DIR            "Not a directory"
 #define ERR_NOT_AN_ARCHIVE       "Not an archive"
 #define ERR_CORRUPTED            "Corrupted archive"
 #define ERR_SEEK_OUT_OF_RANGE    "Seek out of range"
 #define ERR_BAD_FILENAME         "Bad filename"
 #define ERR_PHYSFS_BAD_OS_CALL   "(BUG) PhysicsFS made a bad system call"
 #define ERR_ARGV0_IS_NULL        "argv0 is NULL"
 #define ERR_NEED_DICT            "need dictionary"
 #define ERR_DATA_ERROR           "data error"
 #define ERR_MEMORY_ERROR         "memory error"
 #define ERR_BUFFER_ERROR         "buffer error"
 #define ERR_VERSION_ERROR        "version error"
 #define ERR_UNKNOWN_ERROR        "unknown error"
 #define ERR_SEARCHPATH_TRUNC     "Search path was truncated"
 #define ERR_GETMODFN_TRUNC       "GetModuleFileName() was truncated"
 #define ERR_GETMODFN_NO_DIR      "GetModuleFileName() had no dir"
 #define ERR_DISK_FULL            "Disk is full"
 #define ERR_DIRECTORY_FULL       "Directory full"
 #define ERR_MACOS_GENERIC        "MacOS reported error (%d)"
 #define ERR_OS2_GENERIC          "OS/2 reported error (%d)"
 #define ERR_VOL_LOCKED_HW        "Volume is locked through hardware"
 #define ERR_VOL_LOCKED_SW        "Volume is locked through software"
 #define ERR_FILE_LOCKED          "File is locked"
 #define ERR_FILE_OR_DIR_BUSY     "File/directory is busy"
 #define ERR_FILE_ALREADY_OPEN_W  "File already open for writing"
 #define ERR_FILE_ALREADY_OPEN_R  "File already open for reading"
 #define ERR_INVALID_REFNUM       "Invalid reference number"
 #define ERR_GETTING_FILE_POS     "Error getting file position"
 #define ERR_VOLUME_OFFLINE       "Volume is offline"
 #define ERR_PERMISSION_DENIED    "Permission denied"
 #define ERR_VOL_ALREADY_ONLINE   "Volume already online"
 #define ERR_NO_SUCH_DRIVE        "No such drive"
 #define ERR_NOT_MAC_DISK         "Not a Macintosh disk"
 #define ERR_VOL_EXTERNAL_FS      "Volume belongs to an external filesystem"
 #define ERR_PROBLEM_RENAME       "Problem during rename"
 #define ERR_BAD_MASTER_BLOCK     "Bad master directory block"
 #define ERR_CANT_MOVE_FORBIDDEN  "Attempt to move forbidden"
 #define ERR_WRONG_VOL_TYPE       "Wrong volume type"
 #define ERR_SERVER_VOL_LOST      "Server volume has been disconnected"
 #define ERR_FILE_ID_NOT_FOUND    "File ID not found"
 #define ERR_FILE_ID_EXISTS       "File ID already exists"
 #define ERR_SERVER_NO_RESPOND    "Server not responding"
 #define ERR_USER_AUTH_FAILED     "User authentication failed"
 #define ERR_PWORD_EXPIRED        "Password has expired on server"
 #define ERR_ACCESS_DENIED        "Access denied"
 #define ERR_NOT_A_DOS_DISK       "Not a DOS disk"
 #define ERR_SHARING_VIOLATION    "Sharing violation"
 #define ERR_CANNOT_MAKE          "Cannot make"
 #define ERR_DEV_IN_USE           "Device already in use"
 #define ERR_OPEN_FAILED          "Open failed"
 #define ERR_PIPE_BUSY            "Pipe is busy"
 #define ERR_SHARING_BUF_EXCEEDED "Sharing buffer exceeded"
 #define ERR_TOO_MANY_HANDLES     "Too many open handles"
 #define ERR_SEEK_ERROR           "Seek error"
 #define ERR_DEL_CWD              "Trying to delete current working directory"
 #define ERR_WRITE_PROTECT_ERROR  "Write protect error"
 #define ERR_WRITE_FAULT          "Write fault"
 #define ERR_LOCK_VIOLATION       "Lock violation"
 #define ERR_GEN_FAILURE          "General failure"
 #define ERR_UNCERTAIN_MEDIA      "Uncertain media"
 #define ERR_PROT_VIOLATION       "Protection violation"
 #define ERR_BROKEN_PIPE          "Broken pipe"

#elif (PHYSFS_LANG == PHYSFS_LANG_GERMAN)
 #define DIR_ARCHIVE_DESCRIPTION  "Kein Archiv, direkte Ein/Ausgabe in das Dateisystem"
 #define GRP_ARCHIVE_DESCRIPTION  "Build engine Groupfile format"
 #define HOG_ARCHIVE_DESCRIPTION  "Descent I/II HOG file format"
 #define MVL_ARCHIVE_DESCRIPTION  "Descent II Movielib format"
 #define QPAK_ARCHIVE_DESCRIPTION "Quake I/II format"
 #define ZIP_ARCHIVE_DESCRIPTION  "PkZip/WinZip/Info-Zip kompatibel"
 #define WAD_ARCHIVE_DESCRIPTION  "DOOM engine format" /* !!! FIXME: translate this line if needed */
 #define LZMA_ARCHIVE_DESCRIPTION "LZMA (7zip) format" /* !!! FIXME: translate this line if needed */

 #define ERR_IS_INITIALIZED       "Bereits initialisiert"
 #define ERR_NOT_INITIALIZED      "Nicht initialisiert"
 #define ERR_INVALID_ARGUMENT     "Ung�ltiges Argument"
 #define ERR_FILES_STILL_OPEN     "Dateien noch immer ge�ffnet"
 #define ERR_NO_DIR_CREATE        "Fehler beim Erzeugen der Verzeichnisse"
 #define ERR_OUT_OF_MEMORY        "Kein Speicher mehr frei"
 #define ERR_NOT_IN_SEARCH_PATH   "Eintrag nicht im Suchpfad enthalten"
 #define ERR_NOT_SUPPORTED        "Befehl nicht unterst�tzt"
 #define ERR_UNSUPPORTED_ARCHIVE  "Archiv-Typ nicht unterst�tzt"
 #define ERR_NOT_A_HANDLE         "Ist kein Dateideskriptor"
 #define ERR_INSECURE_FNAME       "Unsicherer Dateiname"
 #define ERR_SYMLINK_DISALLOWED   "Symbolische Verweise deaktiviert"
 #define ERR_NO_WRITE_DIR         "Schreibverzeichnis ist nicht gesetzt"
 #define ERR_NO_SUCH_FILE         "Datei nicht gefunden"
 #define ERR_NO_SUCH_PATH         "Pfad nicht gefunden"
 #define ERR_NO_SUCH_VOLUME       "Datencontainer nicht gefunden"
 #define ERR_PAST_EOF             "Hinter dem Ende der Datei"
 #define ERR_ARC_IS_READ_ONLY     "Archiv ist schreibgesch�tzt"
 #define ERR_IO_ERROR             "Ein/Ausgabe Fehler"
 #define ERR_CANT_SET_WRITE_DIR   "Kann Schreibverzeichnis nicht setzen"
 #define ERR_SYMLINK_LOOP         "Endlosschleife durch symbolische Verweise"
 #define ERR_COMPRESSION          "(De)Kompressionsfehler"
 #define ERR_NOT_IMPLEMENTED      "Nicht implementiert"
 #define ERR_OS_ERROR             "Betriebssystem meldete Fehler"
 #define ERR_FILE_EXISTS          "Datei existiert bereits"
 #define ERR_NOT_A_FILE           "Ist keine Datei"
 #define ERR_NOT_A_DIR            "Ist kein Verzeichnis"
 #define ERR_NOT_AN_ARCHIVE       "Ist kein Archiv"
 #define ERR_CORRUPTED            "Besch�digtes Archiv"
 #define ERR_SEEK_OUT_OF_RANGE    "Suche war ausserhalb der Reichweite"
 #define ERR_BAD_FILENAME         "Unzul�ssiger Dateiname"
 #define ERR_PHYSFS_BAD_OS_CALL   "(BUG) PhysicsFS verursachte einen ung�ltigen Systemaufruf"
 #define ERR_ARGV0_IS_NULL        "argv0 ist NULL"
 #define ERR_NEED_DICT            "brauche W�rterbuch"
 #define ERR_DATA_ERROR           "Datenfehler"
 #define ERR_MEMORY_ERROR         "Speicherfehler"
 #define ERR_BUFFER_ERROR         "Bufferfehler"
 #define ERR_VERSION_ERROR        "Versionskonflikt"
 #define ERR_UNKNOWN_ERROR        "Unbekannter Fehler"
 #define ERR_SEARCHPATH_TRUNC     "Suchpfad war abgeschnitten"
 #define ERR_GETMODFN_TRUNC       "GetModuleFileName() war abgeschnitten"
 #define ERR_GETMODFN_NO_DIR      "GetModuleFileName() bekam kein Verzeichnis"
 #define ERR_DISK_FULL            "Laufwerk ist voll"
 #define ERR_DIRECTORY_FULL       "Verzeichnis ist voll"
 #define ERR_MACOS_GENERIC        "MacOS meldete Fehler (%d)"
 #define ERR_OS2_GENERIC          "OS/2 meldete Fehler (%d)"
 #define ERR_VOL_LOCKED_HW        "Datencontainer ist durch Hardware gesperrt"
 #define ERR_VOL_LOCKED_SW        "Datencontainer ist durch Software gesperrt"
 #define ERR_FILE_LOCKED          "Datei ist gesperrt"
 #define ERR_FILE_OR_DIR_BUSY     "Datei/Verzeichnis ist besch�ftigt"
 #define ERR_FILE_ALREADY_OPEN_W  "Datei schon im Schreibmodus ge�ffnet"
 #define ERR_FILE_ALREADY_OPEN_R  "Datei schon im Lesemodus ge�ffnet"
 #define ERR_INVALID_REFNUM       "Ung�ltige Referenznummer"
 #define ERR_GETTING_FILE_POS     "Fehler beim Finden der Dateiposition"
 #define ERR_VOLUME_OFFLINE       "Datencontainer ist offline"
 #define ERR_PERMISSION_DENIED    "Zugriff verweigert"
 #define ERR_VOL_ALREADY_ONLINE   "Datencontainer ist bereits online"
 #define ERR_NO_SUCH_DRIVE        "Laufwerk nicht vorhanden"
 #define ERR_NOT_MAC_DISK         "Ist kein Macintosh Laufwerk"
 #define ERR_VOL_EXTERNAL_FS      "Datencontainer liegt auf einem externen Dateisystem"
 #define ERR_PROBLEM_RENAME       "Fehler beim Umbenennen"
 #define ERR_BAD_MASTER_BLOCK     "Besch�digter Hauptverzeichnisblock"
 #define ERR_CANT_MOVE_FORBIDDEN  "Verschieben nicht erlaubt"
 #define ERR_WRONG_VOL_TYPE       "Falscher Datencontainer-Typ"
 #define ERR_SERVER_VOL_LOST      "Datencontainer am Server wurde getrennt"
 #define ERR_FILE_ID_NOT_FOUND    "Dateikennung nicht gefunden"
 #define ERR_FILE_ID_EXISTS       "Dateikennung existiert bereits"
 #define ERR_SERVER_NO_RESPOND    "Server antwortet nicht"
 #define ERR_USER_AUTH_FAILED     "Benutzerauthentifizierung fehlgeschlagen"
 #define ERR_PWORD_EXPIRED        "Passwort am Server ist abgelaufen"
 #define ERR_ACCESS_DENIED        "Zugriff verweigert"
 #define ERR_NOT_A_DOS_DISK       "Ist kein DOS-Laufwerk"
 #define ERR_SHARING_VIOLATION    "Zugriffsverletzung"
 #define ERR_CANNOT_MAKE          "Kann nicht erzeugen"
 #define ERR_DEV_IN_USE           "Ger�t wird bereits benutzt"
 #define ERR_OPEN_FAILED          "�ffnen fehlgeschlagen"
 #define ERR_PIPE_BUSY            "Pipeverbindung ist belegt"
 #define ERR_SHARING_BUF_EXCEEDED "Zugriffsbuffer �berschritten"
 #define ERR_TOO_MANY_HANDLES     "Zu viele offene Dateien"
 #define ERR_SEEK_ERROR           "Fehler beim Suchen"
 #define ERR_DEL_CWD              "Aktuelles Arbeitsverzeichnis darf nicht gel�scht werden"
 #define ERR_WRITE_PROTECT_ERROR  "Schreibschutzfehler"
 #define ERR_WRITE_FAULT          "Schreibfehler"
 #define ERR_LOCK_VIOLATION       "Sperrverletzung"
 #define ERR_GEN_FAILURE          "Allgemeiner Fehler"
 #define ERR_UNCERTAIN_MEDIA      "Unsicheres Medium"
 #define ERR_PROT_VIOLATION       "Schutzverletzung"
 #define ERR_BROKEN_PIPE          "Pipeverbindung unterbrochen"

#elif (PHYSFS_LANG == PHYSFS_LANG_RUSSIAN_KOI8_R)
 #define DIR_ARCHIVE_DESCRIPTION  "�� �����, ���������������� ����/����� �������� �������"
 #define GRP_ARCHIVE_DESCRIPTION  "������ ���������� ����� Build engine"
 #define HOG_ARCHIVE_DESCRIPTION  "Descent I/II HOG file format"
 #define MVL_ARCHIVE_DESCRIPTION  "Descent II Movielib format"
 #define ZIP_ARCHIVE_DESCRIPTION  "PkZip/WinZip/Info-Zip �����������"
 #define WAD_ARCHIVE_DESCRIPTION  "DOOM engine format" /* !!! FIXME: translate this line if needed */
 #define LZMA_ARCHIVE_DESCRIPTION "LZMA (7zip) format" /* !!! FIXME: translate this line if needed */

 #define ERR_IS_INITIALIZED       "��� ���������������"
 #define ERR_NOT_INITIALIZED      "�� ���������������"
 #define ERR_INVALID_ARGUMENT     "�������� ��������"
 #define ERR_FILES_STILL_OPEN     "����� ��� �������"
 #define ERR_NO_DIR_CREATE        "�� ���� ������� ��������"
 #define ERR_OUT_OF_MEMORY        "��������� ������"
 #define ERR_NOT_IN_SEARCH_PATH   "��� ������ �������� � ���� ������"
 #define ERR_NOT_SUPPORTED        "�������� �� ��������������"
 #define ERR_UNSUPPORTED_ARCHIVE  "������ ������ ���� �� ��������������"
 #define ERR_NOT_A_HANDLE         "�� �������� ����������"
 #define ERR_INSECURE_FNAME       "������������ ��� �����"
 #define ERR_SYMLINK_DISALLOWED   "���������� ������ ���������"
 #define ERR_NO_WRITE_DIR         "������� ��� ������ �� ����������"
 #define ERR_NO_SUCH_FILE         "���� �� ������"
 #define ERR_NO_SUCH_PATH         "���� �� ������"
 #define ERR_NO_SUCH_VOLUME       "��� �� ������"
 #define ERR_PAST_EOF             "�� ������ �����"
 #define ERR_ARC_IS_READ_ONLY     "����� ������ ��� ������"
 #define ERR_IO_ERROR             "������ �����/������"
 #define ERR_CANT_SET_WRITE_DIR   "�� ���� ���������� ������� ��� ������"
 #define ERR_SYMLINK_LOOP         "����������� ���� ���������� ������"
 #define ERR_COMPRESSION          "������ (���)�������"
 #define ERR_NOT_IMPLEMENTED      "�� �����������"
 #define ERR_OS_ERROR             "������������ ������� �������� ������"
 #define ERR_FILE_EXISTS          "���� ��� ����������"
 #define ERR_NOT_A_FILE           "�� ����"
 #define ERR_NOT_A_DIR            "�� �������"
 #define ERR_NOT_AN_ARCHIVE       "�� �����"
 #define ERR_CORRUPTED            "������������ �����"
 #define ERR_SEEK_OUT_OF_RANGE    "���������������� �� �������"
 #define ERR_BAD_FILENAME         "�������� ��� �����"
 #define ERR_PHYSFS_BAD_OS_CALL   "(BUG) PhysicsFS ��������� �������� ��������� �����"
 #define ERR_ARGV0_IS_NULL        "argv0 is NULL"
 #define ERR_NEED_DICT            "����� �������"
 #define ERR_DATA_ERROR           "������ ������"
 #define ERR_MEMORY_ERROR         "������ ������"
 #define ERR_BUFFER_ERROR         "������ ������"
 #define ERR_VERSION_ERROR        "������ ������"
 #define ERR_UNKNOWN_ERROR        "����������� ������"
 #define ERR_SEARCHPATH_TRUNC     "���� ������ �������"
 #define ERR_GETMODFN_TRUNC       "GetModuleFileName() �������"
 #define ERR_GETMODFN_NO_DIR      "GetModuleFileName() �� ������� �������"
 #define ERR_DISK_FULL            "���� �����"
 #define ERR_DIRECTORY_FULL       "������� �����"
 #define ERR_MACOS_GENERIC        "MacOS �������� ������ (%d)"
 #define ERR_OS2_GENERIC          "OS/2 �������� ������ (%d)"
 #define ERR_VOL_LOCKED_HW        "��� ���������� ���������"
 #define ERR_VOL_LOCKED_SW        "��� ���������� ����������"
 #define ERR_FILE_LOCKED          "���� ������������"
 #define ERR_FILE_OR_DIR_BUSY     "����/������� �����"
 #define ERR_FILE_ALREADY_OPEN_W  "���� ��� ������ �� ������"
 #define ERR_FILE_ALREADY_OPEN_R  "���� ��� ������ �� ������"
 #define ERR_INVALID_REFNUM       "�������� ���������� ������"
 #define ERR_GETTING_FILE_POS     "������ ��� ��������� ������� �����"
 #define ERR_VOLUME_OFFLINE       "��� ����������"
 #define ERR_PERMISSION_DENIED    "�������� � ����������"
 #define ERR_VOL_ALREADY_ONLINE   "��� ��� �����������"
 #define ERR_NO_SUCH_DRIVE        "��� ������ �����"
 #define ERR_NOT_MAC_DISK         "�� ���� Macintosh"
 #define ERR_VOL_EXTERNAL_FS      "��� ����������� ������� �������� �������"
 #define ERR_PROBLEM_RENAME       "�������� ��� ��������������"
 #define ERR_BAD_MASTER_BLOCK     "������ ������� ���� ��������"
 #define ERR_CANT_MOVE_FORBIDDEN  "������� ����������� ���������"
 #define ERR_WRONG_VOL_TYPE       "�������� ��� ����"
 #define ERR_SERVER_VOL_LOST      "��������� ��� ��� ����������"
 #define ERR_FILE_ID_NOT_FOUND    "������������� ����� �� ������"
 #define ERR_FILE_ID_EXISTS       "������������� ����� ��� ����������"
 #define ERR_SERVER_NO_RESPOND    "������ �� ��������"
 #define ERR_USER_AUTH_FAILED     "������������� ������������ �� �������"
 #define ERR_PWORD_EXPIRED        "������ �� ������� �������"
 #define ERR_ACCESS_DENIED        "�������� � �������"
 #define ERR_NOT_A_DOS_DISK       "�� ���� DOS"
 #define ERR_SHARING_VIOLATION    "��������� ����������� �������"
 #define ERR_CANNOT_MAKE          "�� ���� �������"
 #define ERR_DEV_IN_USE           "���������� ��� ������������"
 #define ERR_OPEN_FAILED          "�������� �� �������"
 #define ERR_PIPE_BUSY            "�������� �����"
 #define ERR_SHARING_BUF_EXCEEDED "����������� ����� ����������"
 #define ERR_TOO_MANY_HANDLES     "������� ����� �������� ������������"
 #define ERR_SEEK_ERROR           "������ ����������������"
 #define ERR_DEL_CWD              "������� ������� ������� ������� �������"
 #define ERR_WRITE_PROTECT_ERROR  "������ ������ ������"
 #define ERR_WRITE_FAULT          "������ ������"
 #define ERR_LOCK_VIOLATION       "��������� ����������"
 #define ERR_GEN_FAILURE          "����� ����"
 #define ERR_UNCERTAIN_MEDIA      "�������������� ��������"
 #define ERR_PROT_VIOLATION       "��������� ������"
 #define ERR_BROKEN_PIPE          "��������� ��������"

#elif (PHYSFS_LANG == PHYSFS_LANG_RUSSIAN_CP1251)
 #define DIR_ARCHIVE_DESCRIPTION  "�� �����, ���������������� ����/����� �������� �������"
 #define GRP_ARCHIVE_DESCRIPTION  "������ ���������� ����� Build engine"
 #define HOG_ARCHIVE_DESCRIPTION  "Descent I/II HOG file format"
 #define MVL_ARCHIVE_DESCRIPTION  "Descent II Movielib format"
 #define ZIP_ARCHIVE_DESCRIPTION  "PkZip/WinZip/Info-Zip �����������"
 #define WAD_ARCHIVE_DESCRIPTION  "DOOM engine format" /* !!! FIXME: translate this line if needed */
 #define LZMA_ARCHIVE_DESCRIPTION "LZMA (7zip) format" /* !!! FIXME: translate this line if needed */

 #define ERR_IS_INITIALIZED       "��� ���������������"
 #define ERR_NOT_INITIALIZED      "�� ���������������"
 #define ERR_INVALID_ARGUMENT     "�������� ��������"
 #define ERR_FILES_STILL_OPEN     "����� ��� �������"
 #define ERR_NO_DIR_CREATE        "�� ���� ������� ��������"
 #define ERR_OUT_OF_MEMORY        "��������� ������"
 #define ERR_NOT_IN_SEARCH_PATH   "��� ������ �������� � ���� ������"
 #define ERR_NOT_SUPPORTED        "�������� �� ��������������"
 #define ERR_UNSUPPORTED_ARCHIVE  "������ ������ ���� �� ��������������"
 #define ERR_NOT_A_HANDLE         "�� �������� ����������"
 #define ERR_INSECURE_FNAME       "������������ ��� �����"
 #define ERR_SYMLINK_DISALLOWED   "���������� ������ ���������"
 #define ERR_NO_WRITE_DIR         "������� ��� ������ �� ����������"
 #define ERR_NO_SUCH_FILE         "���� �� ������"
 #define ERR_NO_SUCH_PATH         "���� �� ������"
 #define ERR_NO_SUCH_VOLUME       "��� �� ������"
 #define ERR_PAST_EOF             "�� ������ �����"
 #define ERR_ARC_IS_READ_ONLY     "����� ������ ��� ������"
 #define ERR_IO_ERROR             "������ �����/������"
 #define ERR_CANT_SET_WRITE_DIR   "�� ���� ���������� ������� ��� ������"
 #define ERR_SYMLINK_LOOP         "����������� ���� ���������� ������"
 #define ERR_COMPRESSION          "������ (���)�������"
 #define ERR_NOT_IMPLEMENTED      "�� �����������"
 #define ERR_OS_ERROR             "������������ ������� �������� ������"
 #define ERR_FILE_EXISTS          "���� ��� ����������"
 #define ERR_NOT_A_FILE           "�� ����"
 #define ERR_NOT_A_DIR            "�� �������"
 #define ERR_NOT_AN_ARCHIVE       "�� �����"
 #define ERR_CORRUPTED            "������������ �����"
 #define ERR_SEEK_OUT_OF_RANGE    "���������������� �� �������"
 #define ERR_BAD_FILENAME         "�������� ��� �����"
 #define ERR_PHYSFS_BAD_OS_CALL   "(BUG) PhysicsFS ��������� �������� ��������� �����"
 #define ERR_ARGV0_IS_NULL        "argv0 is NULL"
 #define ERR_NEED_DICT            "����� �������"
 #define ERR_DATA_ERROR           "������ ������"
 #define ERR_MEMORY_ERROR         "������ ������"
 #define ERR_BUFFER_ERROR         "������ ������"
 #define ERR_VERSION_ERROR        "������ ������"
 #define ERR_UNKNOWN_ERROR        "����������� ������"
 #define ERR_SEARCHPATH_TRUNC     "���� ������ �������"
 #define ERR_GETMODFN_TRUNC       "GetModuleFileName() �������"
 #define ERR_GETMODFN_NO_DIR      "GetModuleFileName() �� ������� �������"
 #define ERR_DISK_FULL            "���� �����"
 #define ERR_DIRECTORY_FULL       "������� �����"
 #define ERR_MACOS_GENERIC        "MacOS �������� ������ (%d)"
 #define ERR_OS2_GENERIC          "OS/2 �������� ������ (%d)"
 #define ERR_VOL_LOCKED_HW        "��� ���������� ���������"
 #define ERR_VOL_LOCKED_SW        "��� ���������� ����������"
 #define ERR_FILE_LOCKED          "���� ������������"
 #define ERR_FILE_OR_DIR_BUSY     "����/������� �����"
 #define ERR_FILE_ALREADY_OPEN_W  "���� ��� ������ �� ������"
 #define ERR_FILE_ALREADY_OPEN_R  "���� ��� ������ �� ������"
 #define ERR_INVALID_REFNUM       "�������� ���������� ������"
 #define ERR_GETTING_FILE_POS     "������ ��� ��������� ������� �����"
 #define ERR_VOLUME_OFFLINE       "��� ����������"
 #define ERR_PERMISSION_DENIED    "�������� � ����������"
 #define ERR_VOL_ALREADY_ONLINE   "��� ��� �����������"
 #define ERR_NO_SUCH_DRIVE        "��� ������ �����"
 #define ERR_NOT_MAC_DISK         "�� ���� Macintosh"
 #define ERR_VOL_EXTERNAL_FS      "��� ����������� ������� �������� �������"
 #define ERR_PROBLEM_RENAME       "�������� ��� ��������������"
 #define ERR_BAD_MASTER_BLOCK     "������ ������� ���� ��������"
 #define ERR_CANT_MOVE_FORBIDDEN  "������� ����������� ���������"
 #define ERR_WRONG_VOL_TYPE       "�������� ��� ����"
 #define ERR_SERVER_VOL_LOST      "��������� ��� ��� ����������"
 #define ERR_FILE_ID_NOT_FOUND    "������������� ����� �� ������"
 #define ERR_FILE_ID_EXISTS       "������������� ����� ��� ����������"
 #define ERR_SERVER_NO_RESPOND    "������ �� ��������"
 #define ERR_USER_AUTH_FAILED     "������������� ������������ �� �������"
 #define ERR_PWORD_EXPIRED        "������ �� ������� �������"
 #define ERR_ACCESS_DENIED        "�������� � �������"
 #define ERR_NOT_A_DOS_DISK       "�� ���� DOS"
 #define ERR_SHARING_VIOLATION    "��������� ����������� �������"
 #define ERR_CANNOT_MAKE          "�� ���� �������"
 #define ERR_DEV_IN_USE           "���������� ��� ������������"
 #define ERR_OPEN_FAILED          "�������� �� �������"
 #define ERR_PIPE_BUSY            "�������� �����"
 #define ERR_SHARING_BUF_EXCEEDED "����������� ����� ����������"
 #define ERR_TOO_MANY_HANDLES     "������� ����� �������� ������������"
 #define ERR_SEEK_ERROR           "������ ����������������"
 #define ERR_DEL_CWD              "������� ������� ������� ������� �������"
 #define ERR_WRITE_PROTECT_ERROR  "������ ������ ������"
 #define ERR_WRITE_FAULT          "������ ������"
 #define ERR_LOCK_VIOLATION       "��������� ����������"
 #define ERR_GEN_FAILURE          "����� ����"
 #define ERR_UNCERTAIN_MEDIA      "�������������� ��������"
 #define ERR_PROT_VIOLATION       "��������� ������"
 #define ERR_BROKEN_PIPE          "��������� ��������"

#elif (PHYSFS_LANG == PHYSFS_LANG_RUSSIAN_CP866)
 #define DIR_ARCHIVE_DESCRIPTION  "�� ��娢, �����।�⢥��� ����/�뢮� 䠩����� ��⥬�"
 #define GRP_ARCHIVE_DESCRIPTION  "��ଠ� ��㯯����� 䠩�� Build engine"
 #define HOG_ARCHIVE_DESCRIPTION  "Descent I/II HOG file format"
 #define MVL_ARCHIVE_DESCRIPTION  "Descent II Movielib format"
 #define ZIP_ARCHIVE_DESCRIPTION  "PkZip/WinZip/Info-Zip ᮢ���⨬�"
 #define WAD_ARCHIVE_DESCRIPTION  "DOOM engine format" /* !!! FIXME: translate this line if needed */
 #define LZMA_ARCHIVE_DESCRIPTION "LZMA (7zip) format" /* !!! FIXME: translate this line if needed */

 #define ERR_IS_INITIALIZED       "��� ���樠����஢��"
 #define ERR_NOT_INITIALIZED      "�� ���樠����஢��"
 #define ERR_INVALID_ARGUMENT     "������ ��㬥��"
 #define ERR_FILES_STILL_OPEN     "����� �� ������"
 #define ERR_NO_DIR_CREATE        "�� ���� ᮧ���� ��⠫���"
 #define ERR_OUT_OF_MEMORY        "���稫��� ������"
 #define ERR_NOT_IN_SEARCH_PATH   "��� ⠪��� ����� � ��� ���᪠"
 #define ERR_NOT_SUPPORTED        "������ �� �����ন������"
 #define ERR_UNSUPPORTED_ARCHIVE  "��娢� ⠪��� ⨯� �� �����ন������"
 #define ERR_NOT_A_HANDLE         "�� 䠩���� ���ਯ��"
 #define ERR_INSECURE_FNAME       "��������᭮� ��� 䠩��"
 #define ERR_SYMLINK_DISALLOWED   "�������� ��뫪� �⪫�祭�"
 #define ERR_NO_WRITE_DIR         "��⠫�� ��� ����� �� ��⠭�����"
 #define ERR_NO_SUCH_FILE         "���� �� ������"
 #define ERR_NO_SUCH_PATH         "���� �� ������"
 #define ERR_NO_SUCH_VOLUME       "��� �� ������"
 #define ERR_PAST_EOF             "�� ���殬 䠩��"
 #define ERR_ARC_IS_READ_ONLY     "��娢 ⮫쪮 ��� �⥭��"
 #define ERR_IO_ERROR             "�訡�� �����/�뢮��"
 #define ERR_CANT_SET_WRITE_DIR   "�� ���� ��⠭����� ��⠫�� ��� �����"
 #define ERR_SYMLINK_LOOP         "��᪮���� 横� ᨬ���쭮� ��뫪�"
 #define ERR_COMPRESSION          "�訡�� (���)�������"
 #define ERR_NOT_IMPLEMENTED      "�� ॠ��������"
 #define ERR_OS_ERROR             "����樮���� ��⥬� ᮮ�騫� �訡��"
 #define ERR_FILE_EXISTS          "���� 㦥 �������"
 #define ERR_NOT_A_FILE           "�� 䠩�"
 #define ERR_NOT_A_DIR            "�� ��⠫��"
 #define ERR_NOT_AN_ARCHIVE       "�� ��娢"
 #define ERR_CORRUPTED            "���०����� ��娢"
 #define ERR_SEEK_OUT_OF_RANGE    "����樮��஢���� �� �।���"
 #define ERR_BAD_FILENAME         "����୮� ��� 䠩��"
 #define ERR_PHYSFS_BAD_OS_CALL   "(BUG) PhysicsFS �믮����� ������ ��⥬�� �맮�"
 #define ERR_ARGV0_IS_NULL        "argv0 is NULL"
 #define ERR_NEED_DICT            "�㦥� ᫮����"
 #define ERR_DATA_ERROR           "�訡�� ������"
 #define ERR_MEMORY_ERROR         "�訡�� �����"
 #define ERR_BUFFER_ERROR         "�訡�� ����"
 #define ERR_VERSION_ERROR        "�訡�� ���ᨨ"
 #define ERR_UNKNOWN_ERROR        "�������⭠� �訡��"
 #define ERR_SEARCHPATH_TRUNC     "���� ���᪠ ��१��"
 #define ERR_GETMODFN_TRUNC       "GetModuleFileName() ��१��"
 #define ERR_GETMODFN_NO_DIR      "GetModuleFileName() �� ����稫 ��⠫��"
 #define ERR_DISK_FULL            "��� �����"
 #define ERR_DIRECTORY_FULL       "��⠫�� �����"
 #define ERR_MACOS_GENERIC        "MacOS ᮮ�騫� �訡�� (%d)"
 #define ERR_OS2_GENERIC          "OS/2 ᮮ�騫� �訡�� (%d)"
 #define ERR_VOL_LOCKED_HW        "��� �����஢�� �����⭮"
 #define ERR_VOL_LOCKED_SW        "��� �����஢�� �ணࠬ���"
 #define ERR_FILE_LOCKED          "���� �������஢��"
 #define ERR_FILE_OR_DIR_BUSY     "����/��⠫�� �����"
 #define ERR_FILE_ALREADY_OPEN_W  "���� 㦥 ����� �� ������"
 #define ERR_FILE_ALREADY_OPEN_R  "���� 㦥 ����� �� �⥭��"
 #define ERR_INVALID_REFNUM       "����୮� ������⢮ ��뫮�"
 #define ERR_GETTING_FILE_POS     "�訡�� �� ����祭�� ����樨 䠩��"
 #define ERR_VOLUME_OFFLINE       "��� ��ᮥ�����"
 #define ERR_PERMISSION_DENIED    "�⪠���� � ࠧ�襭��"
 #define ERR_VOL_ALREADY_ONLINE   "��� 㦥 ���ᮥ�����"
 #define ERR_NO_SUCH_DRIVE        "��� ⠪��� ��᪠"
 #define ERR_NOT_MAC_DISK         "�� ��� Macintosh"
 #define ERR_VOL_EXTERNAL_FS      "��� �ਭ������� ���譥� 䠩����� ��⥬�"
 #define ERR_PROBLEM_RENAME       "�஡���� �� ��२���������"
 #define ERR_BAD_MASTER_BLOCK     "���宩 ������ ���� ��⠫���"
 #define ERR_CANT_MOVE_FORBIDDEN  "����⪠ ��६����� ����饭�"
 #define ERR_WRONG_VOL_TYPE       "������ ⨯ ⮬�"
 #define ERR_SERVER_VOL_LOST      "��ࢥ�� ⮬ �� ��ᮥ�����"
 #define ERR_FILE_ID_NOT_FOUND    "�����䨪��� 䠩�� �� ������"
 #define ERR_FILE_ID_EXISTS       "�����䨪��� 䠩�� 㦥 �������"
 #define ERR_SERVER_NO_RESPOND    "��ࢥ� �� �⢥砥�"
 #define ERR_USER_AUTH_FAILED     "�����䨪��� ���짮��⥫� �� 㤠����"
 #define ERR_PWORD_EXPIRED        "��஫� �� �ࢥ� ���५"
 #define ERR_ACCESS_DENIED        "�⪠���� � ����㯥"
 #define ERR_NOT_A_DOS_DISK       "�� ��� DOS"
 #define ERR_SHARING_VIOLATION    "����襭�� ᮢ���⭮�� ����㯠"
 #define ERR_CANNOT_MAKE          "�� ���� ᮡ���"
 #define ERR_DEV_IN_USE           "���ன�⢮ 㦥 �ᯮ������"
 #define ERR_OPEN_FAILED          "����⨥ �� 㤠����"
 #define ERR_PIPE_BUSY            "�������� �����"
 #define ERR_SHARING_BUF_EXCEEDED "������塞� ���� ��९�����"
 #define ERR_TOO_MANY_HANDLES     "���誮� ����� ������� ���ਯ�஢"
 #define ERR_SEEK_ERROR           "�訡�� ����樮��஢����"
 #define ERR_DEL_CWD              "����⪠ 㤠���� ⥪�騩 ࠡ�稩 ��⠫��"
 #define ERR_WRITE_PROTECT_ERROR  "�訡�� ����� �����"
 #define ERR_WRITE_FAULT          "�訡�� �����"
 #define ERR_LOCK_VIOLATION       "����襭�� �����஢��"
 #define ERR_GEN_FAILURE          "��騩 ᡮ�"
 #define ERR_UNCERTAIN_MEDIA      "����।������ ���⥫�"
 #define ERR_PROT_VIOLATION       "����襭�� �����"
 #define ERR_BROKEN_PIPE          "�������� ��������"

#elif (PHYSFS_LANG == PHYSFS_LANG_RUSSIAN_ISO_8859_5)
 #define DIR_ARCHIVE_DESCRIPTION  "�� �����, ���������������� ����/����� �������� �������"
 #define GRP_ARCHIVE_DESCRIPTION  "������ ���������� ����� Build engine"
 #define HOG_ARCHIVE_DESCRIPTION  "Descent I/II HOG file format"
 #define MVL_ARCHIVE_DESCRIPTION  "Descent II Movielib format"
 #define ZIP_ARCHIVE_DESCRIPTION  "PkZip/WinZip/Info-Zip �����������"
 #define WAD_ARCHIVE_DESCRIPTION  "DOOM engine format" /* !!! FIXME: translate this line if needed */
 #define LZMA_ARCHIVE_DESCRIPTION "LZMA (7zip) format" /* !!! FIXME: translate this line if needed */

 #define ERR_IS_INITIALIZED       "��� ���������������"
 #define ERR_NOT_INITIALIZED      "�� ���������������"
 #define ERR_INVALID_ARGUMENT     "�������� ��������"
 #define ERR_FILES_STILL_OPEN     "����� ��� �������"
 #define ERR_NO_DIR_CREATE        "�� ���� ������� ��������"
 #define ERR_OUT_OF_MEMORY        "��������� ������"
 #define ERR_NOT_IN_SEARCH_PATH   "��� ������ �������� � ���� ������"
 #define ERR_NOT_SUPPORTED        "�������� �� ��������������"
 #define ERR_UNSUPPORTED_ARCHIVE  "������ ������ ���� �� ��������������"
 #define ERR_NOT_A_HANDLE         "�� �������� ����������"
 #define ERR_INSECURE_FNAME       "������������ ��� �����"
 #define ERR_SYMLINK_DISALLOWED   "���������� ������ ���������"
 #define ERR_NO_WRITE_DIR         "������� ��� ������ �� ����������"
 #define ERR_NO_SUCH_FILE         "���� �� ������"
 #define ERR_NO_SUCH_PATH         "���� �� ������"
 #define ERR_NO_SUCH_VOLUME       "��� �� ������"
 #define ERR_PAST_EOF             "�� ������ �����"
 #define ERR_ARC_IS_READ_ONLY     "����� ������ ��� ������"
 #define ERR_IO_ERROR             "������ �����/������"
 #define ERR_CANT_SET_WRITE_DIR   "�� ���� ���������� ������� ��� ������"
 #define ERR_SYMLINK_LOOP         "����������� ���� ���������� ������"
 #define ERR_COMPRESSION          "������ (���)�������"
 #define ERR_NOT_IMPLEMENTED      "�� �����������"
 #define ERR_OS_ERROR             "������������ ������� �������� ������"
 #define ERR_FILE_EXISTS          "���� ��� ����������"
 #define ERR_NOT_A_FILE           "�� ����"
 #define ERR_NOT_A_DIR            "�� �������"
 #define ERR_NOT_AN_ARCHIVE       "�� �����"
 #define ERR_CORRUPTED            "������������ �����"
 #define ERR_SEEK_OUT_OF_RANGE    "���������������� �� �������"
 #define ERR_BAD_FILENAME         "�������� ��� �����"
 #define ERR_PHYSFS_BAD_OS_CALL   "(BUG) PhysicsFS ��������� �������� ��������� �����"
 #define ERR_ARGV0_IS_NULL        "argv0 is NULL"
 #define ERR_NEED_DICT            "����� �������"
 #define ERR_DATA_ERROR           "������ ������"
 #define ERR_MEMORY_ERROR         "������ ������"
 #define ERR_BUFFER_ERROR         "������ ������"
 #define ERR_VERSION_ERROR        "������ ������"
 #define ERR_UNKNOWN_ERROR        "����������� ������"
 #define ERR_SEARCHPATH_TRUNC     "���� ������ �������"
 #define ERR_GETMODFN_TRUNC       "GetModuleFileName() �������"
 #define ERR_GETMODFN_NO_DIR      "GetModuleFileName() �� ������� �������"
 #define ERR_DISK_FULL            "���� �����"
 #define ERR_DIRECTORY_FULL       "������� �����"
 #define ERR_MACOS_GENERIC        "MacOS �������� ������ (%d)"
 #define ERR_OS2_GENERIC          "OS/2 �������� ������ (%d)"
 #define ERR_VOL_LOCKED_HW        "��� ���������� ���������"
 #define ERR_VOL_LOCKED_SW        "��� ���������� ����������"
 #define ERR_FILE_LOCKED          "���� ������������"
 #define ERR_FILE_OR_DIR_BUSY     "����/������� �����"
 #define ERR_FILE_ALREADY_OPEN_W  "���� ��� ������ �� ������"
 #define ERR_FILE_ALREADY_OPEN_R  "���� ��� ������ �� ������"
 #define ERR_INVALID_REFNUM       "�������� ���������� ������"
 #define ERR_GETTING_FILE_POS     "������ ��� ��������� ������� �����"
 #define ERR_VOLUME_OFFLINE       "��� ����������"
 #define ERR_PERMISSION_DENIED    "�������� � ����������"
 #define ERR_VOL_ALREADY_ONLINE   "��� ��� �����������"
 #define ERR_NO_SUCH_DRIVE        "��� ������ �����"
 #define ERR_NOT_MAC_DISK         "�� ���� Macintosh"
 #define ERR_VOL_EXTERNAL_FS      "��� ����������� ������� �������� �������"
 #define ERR_PROBLEM_RENAME       "�������� ��� ��������������"
 #define ERR_BAD_MASTER_BLOCK     "������ ������� ���� ��������"
 #define ERR_CANT_MOVE_FORBIDDEN  "������� ����������� ���������"
 #define ERR_WRONG_VOL_TYPE       "�������� ��� ����"
 #define ERR_SERVER_VOL_LOST      "��������� ��� ��� ����������"
 #define ERR_FILE_ID_NOT_FOUND    "������������� ����� �� ������"
 #define ERR_FILE_ID_EXISTS       "������������� ����� ��� ����������"
 #define ERR_SERVER_NO_RESPOND    "������ �� ��������"
 #define ERR_USER_AUTH_FAILED     "������������� ������������ �� �������"
 #define ERR_PWORD_EXPIRED        "������ �� ������� �������"
 #define ERR_ACCESS_DENIED        "�������� � �������"
 #define ERR_NOT_A_DOS_DISK       "�� ���� DOS"
 #define ERR_SHARING_VIOLATION    "��������� ����������� �������"
 #define ERR_CANNOT_MAKE          "�� ���� �������"
 #define ERR_DEV_IN_USE           "���������� ��� ������������"
 #define ERR_OPEN_FAILED          "�������� �� �������"
 #define ERR_PIPE_BUSY            "�������� �����"
 #define ERR_SHARING_BUF_EXCEEDED "����������� ����� ����������"
 #define ERR_TOO_MANY_HANDLES     "������� ����� �������� ������������"
 #define ERR_SEEK_ERROR           "������ ����������������"
 #define ERR_DEL_CWD              "������� ������� ������� ������� �������"
 #define ERR_WRITE_PROTECT_ERROR  "������ ������ ������"
 #define ERR_WRITE_FAULT          "������ ������"
 #define ERR_LOCK_VIOLATION       "��������� ����������"
 #define ERR_GEN_FAILURE          "����� ����"
 #define ERR_UNCERTAIN_MEDIA      "�������������� ��������"
 #define ERR_PROT_VIOLATION       "��������� ������"
 #define ERR_BROKEN_PIPE          "��������� ��������"


#elif (PHYSFS_LANG == PHYSFS_LANG_FRENCH)
 #define DIR_ARCHIVE_DESCRIPTION  "Pas d'archive, E/S directes sur syst�me de fichiers"
 #define GRP_ARCHIVE_DESCRIPTION  "Format Groupfile du moteur Build"
 #define HOG_ARCHIVE_DESCRIPTION  "Descent I/II HOG file format"
 #define MVL_ARCHIVE_DESCRIPTION  "Descent II Movielib format"
 #define QPAK_ARCHIVE_DESCRIPTION "Quake I/II format"
 #define ZIP_ARCHIVE_DESCRIPTION  "Compatible PkZip/WinZip/Info-Zip"
 #define WAD_ARCHIVE_DESCRIPTION  "Format WAD du moteur DOOM"
 #define LZMA_ARCHIVE_DESCRIPTION "LZMA (7zip) format" /* !!! FIXME: translate this line if needed */

 #define ERR_IS_INITIALIZED       "D�j� initialis�"
 #define ERR_NOT_INITIALIZED      "Non initialis�"
 #define ERR_INVALID_ARGUMENT     "Argument invalide"
 #define ERR_FILES_STILL_OPEN     "Fichiers encore ouverts"
 #define ERR_NO_DIR_CREATE        "Echec de la cr�ation de r�pertoires"
 #define ERR_OUT_OF_MEMORY        "A court de m�moire"
 #define ERR_NOT_IN_SEARCH_PATH   "Aucune entr�e dans le chemin de recherche"
 #define ERR_NOT_SUPPORTED        "Op�ration non support�e"
 #define ERR_UNSUPPORTED_ARCHIVE  "Type d'archive non support�e"
 #define ERR_NOT_A_HANDLE         "Pas un descripteur de fichier"
 #define ERR_INSECURE_FNAME       "Nom de fichier dangereux"
 #define ERR_SYMLINK_DISALLOWED   "Les liens symboliques sont d�sactiv�s"
 #define ERR_NO_WRITE_DIR         "Le r�pertoire d'�criture n'est pas sp�cifi�"
 #define ERR_NO_SUCH_FILE         "Fichier non trouv�"
 #define ERR_NO_SUCH_PATH         "Chemin non trouv�"
 #define ERR_NO_SUCH_VOLUME       "Volume non trouv�"
 #define ERR_PAST_EOF             "Au-del� de la fin du fichier"
 #define ERR_ARC_IS_READ_ONLY     "L'archive est en lecture seule"
 #define ERR_IO_ERROR             "Erreur E/S"
 #define ERR_CANT_SET_WRITE_DIR   "Ne peut utiliser le r�pertoire d'�criture"
 #define ERR_SYMLINK_LOOP         "Boucle infinie dans les liens symboliques"
 #define ERR_COMPRESSION          "Erreur de (d�)compression"
 #define ERR_NOT_IMPLEMENTED      "Non impl�ment�"
 #define ERR_OS_ERROR             "Erreur rapport�e par le syst�me d'exploitation"
 #define ERR_FILE_EXISTS          "Le fichier existe d�j�"
 #define ERR_NOT_A_FILE           "Pas un fichier"
 #define ERR_NOT_A_DIR            "Pas un r�pertoire"
 #define ERR_NOT_AN_ARCHIVE       "Pas une archive"
 #define ERR_CORRUPTED            "Archive corrompue"
 #define ERR_SEEK_OUT_OF_RANGE    "Pointeur de fichier hors de port�e"
 #define ERR_BAD_FILENAME         "Mauvais nom de fichier"
 #define ERR_PHYSFS_BAD_OS_CALL   "(BOGUE) PhysicsFS a fait un mauvais appel syst�me, le salaud"
 #define ERR_ARGV0_IS_NULL        "argv0 est NULL"
 #define ERR_NEED_DICT            "a besoin du dico"
 #define ERR_DATA_ERROR           "erreur de donn�es"
 #define ERR_MEMORY_ERROR         "erreur m�moire"
 #define ERR_BUFFER_ERROR         "erreur tampon"
 #define ERR_VERSION_ERROR        "erreur de version"
 #define ERR_UNKNOWN_ERROR        "erreur inconnue"
 #define ERR_SEARCHPATH_TRUNC     "Le chemin de recherche a �t� tronqu�"
 #define ERR_GETMODFN_TRUNC       "GetModuleFileName() a �t� tronqu�"
 #define ERR_GETMODFN_NO_DIR      "GetModuleFileName() n'a pas de r�pertoire"
 #define ERR_DISK_FULL            "Disque plein"
 #define ERR_DIRECTORY_FULL       "R�pertoire plein"
 #define ERR_MACOS_GENERIC        "Erreur rapport�e par MacOS (%d)"
 #define ERR_OS2_GENERIC          "Erreur rapport�e par OS/2 (%d)"
 #define ERR_VOL_LOCKED_HW        "Le volume est verrouill� mat�riellement"
 #define ERR_VOL_LOCKED_SW        "Le volume est verrouill� par logiciel"
 #define ERR_FILE_LOCKED          "Fichier verrouill�"
 #define ERR_FILE_OR_DIR_BUSY     "Fichier/r�pertoire occup�"
 #define ERR_FILE_ALREADY_OPEN_W  "Fichier d�j� ouvert en �criture"
 #define ERR_FILE_ALREADY_OPEN_R  "Fichier d�j� ouvert en lecture"
 #define ERR_INVALID_REFNUM       "Num�ro de r�f�rence invalide"
 #define ERR_GETTING_FILE_POS     "Erreur lors de l'obtention de la position du pointeur de fichier"
 #define ERR_VOLUME_OFFLINE       "Le volume n'est pas en ligne"
 #define ERR_PERMISSION_DENIED    "Permission refus�e"
 #define ERR_VOL_ALREADY_ONLINE   "Volum� d�j� en ligne"
 #define ERR_NO_SUCH_DRIVE        "Lecteur inexistant"
 #define ERR_NOT_MAC_DISK         "Pas un disque Macintosh"
 #define ERR_VOL_EXTERNAL_FS      "Le volume appartient � un syst�me de fichiers externe"
 #define ERR_PROBLEM_RENAME       "Probl�me lors du renommage"
 #define ERR_BAD_MASTER_BLOCK     "Mauvais block maitre de r�pertoire"
 #define ERR_CANT_MOVE_FORBIDDEN  "Essai de d�placement interdit"
 #define ERR_WRONG_VOL_TYPE       "Mauvais type de volume"
 #define ERR_SERVER_VOL_LOST      "Le volume serveur a �t� d�connect�"
 #define ERR_FILE_ID_NOT_FOUND    "Identificateur de fichier non trouv�"
 #define ERR_FILE_ID_EXISTS       "Identificateur de fichier existe d�j�"
 #define ERR_SERVER_NO_RESPOND    "Le serveur ne r�pond pas"
 #define ERR_USER_AUTH_FAILED     "Authentification de l'utilisateur �chou�e"
 #define ERR_PWORD_EXPIRED        "Le mot de passe a expir� sur le serveur"
 #define ERR_ACCESS_DENIED        "Acc�s refus�"
 #define ERR_NOT_A_DOS_DISK       "Pas un disque DOS"
 #define ERR_SHARING_VIOLATION    "Violation de partage"
 #define ERR_CANNOT_MAKE          "Ne peut faire"
 #define ERR_DEV_IN_USE           "P�riph�rique d�j� en utilisation"
 #define ERR_OPEN_FAILED          "Ouverture �chou�e"
 #define ERR_PIPE_BUSY            "Le tube est occup�"
 #define ERR_SHARING_BUF_EXCEEDED "Tampon de partage d�pass�"
 #define ERR_TOO_MANY_HANDLES     "Trop de descripteurs ouverts"
 #define ERR_SEEK_ERROR           "Erreur de positionement"
 #define ERR_DEL_CWD              "Essai de supprimer le r�pertoire courant"
 #define ERR_WRITE_PROTECT_ERROR  "Erreur de protection en �criture"
 #define ERR_WRITE_FAULT          "Erreur d'�criture"
 #define ERR_LOCK_VIOLATION       "Violation de verrou"
 #define ERR_GEN_FAILURE          "Echec g�n�ral"
 #define ERR_UNCERTAIN_MEDIA      "M�dia incertain"
 #define ERR_PROT_VIOLATION       "Violation de protection"
 #define ERR_BROKEN_PIPE          "Tube cass�"

#elif (PHYSFS_LANG == PHYSFS_LANG_PORTUGUESE_BR)
 #define DIR_ARCHIVE_DESCRIPTION  "N�o arquivo, E/S sistema de arquivos direto"
 #define GRP_ARCHIVE_DESCRIPTION  "Formato Groupfile do engine Build"
 #define HOG_ARCHIVE_DESCRIPTION  "Formato Descent I/II HOG file"
 #define MVL_ARCHIVE_DESCRIPTION  "Formato Descent II Movielib"
 #define QPAK_ARCHIVE_DESCRIPTION "Formato Quake I/II"
 #define ZIP_ARCHIVE_DESCRIPTION  "Formato compat�vel PkZip/WinZip/Info-Zip"
 #define WAD_ARCHIVE_DESCRIPTION  "Formato WAD do engine DOOM"
 #define WAD_ARCHIVE_DESCRIPTION  "DOOM engine format" /* !!! FIXME: translate this line if needed */
 #define LZMA_ARCHIVE_DESCRIPTION "LZMA (7zip) format" /* !!! FIXME: translate this line if needed */

 #define ERR_IS_INITIALIZED       "J� inicializado"
 #define ERR_NOT_INITIALIZED      "N�o inicializado"
 #define ERR_INVALID_ARGUMENT     "Argumento inv�lido"
 #define ERR_FILES_STILL_OPEN     "Arquivos ainda abertos"
 #define ERR_NO_DIR_CREATE        "Falha na cria��o de diret�rios"
 #define ERR_OUT_OF_MEMORY        "Mem�ria insuficiente"
 #define ERR_NOT_IN_SEARCH_PATH   "Entrada n�o encontrada no caminho de busca"
 #define ERR_NOT_SUPPORTED        "Opera��o n�o suportada"
 #define ERR_UNSUPPORTED_ARCHIVE  "Tipo de arquivo n�o suportado"
 #define ERR_NOT_A_HANDLE         "N�o � um handler de arquivo"
 #define ERR_INSECURE_FNAME       "Nome de arquivo inseguro"
 #define ERR_SYMLINK_DISALLOWED   "Links simb�licos desabilitados"
 #define ERR_NO_WRITE_DIR         "Diret�rio de escrita n�o definido"
 #define ERR_NO_SUCH_FILE         "Arquivo n�o encontrado"
 #define ERR_NO_SUCH_PATH         "Caminho n�o encontrado"
 #define ERR_NO_SUCH_VOLUME       "Volume n�o encontrado"
 #define ERR_PAST_EOF             "Passou o fim do arquivo"
 #define ERR_ARC_IS_READ_ONLY     "Arquivo � somente de leitura"
 #define ERR_IO_ERROR             "Erro de E/S"
 #define ERR_CANT_SET_WRITE_DIR   "N�o foi poss�vel definir diret�rio de escrita"
 #define ERR_SYMLINK_LOOP         "Loop infinito de link simb�lico"
 #define ERR_COMPRESSION          "Erro de (Des)compress�o"
 #define ERR_NOT_IMPLEMENTED      "N�o implementado"
 #define ERR_OS_ERROR             "Erro reportado pelo Sistema Operacional"
 #define ERR_FILE_EXISTS          "Arquivo j� existente"
 #define ERR_NOT_A_FILE           "N�o � um arquivo"
 #define ERR_NOT_A_DIR            "N�o � um diret�rio"
 #define ERR_NOT_AN_ARCHIVE       "N�o � um pacote"
 #define ERR_CORRUPTED            "Pacote corrompido"
 #define ERR_SEEK_OUT_OF_RANGE    "Posicionamento al�m do tamanho"
 #define ERR_BAD_FILENAME         "Nome de arquivo inv�lido"
 #define ERR_PHYSFS_BAD_OS_CALL   "(BUG) PhysicsFS realizou uma chamada de sistema inv�lida"
 #define ERR_ARGV0_IS_NULL        "argv0 � NULL"
 #define ERR_NEED_DICT            "precisa de diret�rio"
 #define ERR_DATA_ERROR           "erro nos dados"
 #define ERR_MEMORY_ERROR         "erro de mem�ria"
 #define ERR_BUFFER_ERROR         "erro de buffer"
 #define ERR_VERSION_ERROR        "erro na version"
 #define ERR_UNKNOWN_ERROR        "erro desconhecido"
 #define ERR_SEARCHPATH_TRUNC     "Caminho de procura quebrado"
 #define ERR_GETMODFN_TRUNC       "GetModuleFileName() foi quebrado"
 #define ERR_GETMODFN_NO_DIR      "GetModuleFileName() nao teve diret�rio"
 #define ERR_DISK_FULL            "Disco cheio"
 #define ERR_DIRECTORY_FULL       "Diret�rio cheio"
 #define ERR_MACOS_GENERIC        "MacOS reportou um erro (%d)"
 #define ERR_OS2_GENERIC          "OS/2 reportou um erro (%d)"
 #define ERR_VOL_LOCKED_HW        "Volume travado por hardware"
 #define ERR_VOL_LOCKED_SW        "Volume travado por software"
 #define ERR_FILE_LOCKED          "Arquivo travado"
 #define ERR_FILE_OR_DIR_BUSY     "Arquivo/Diret�rio est� em uso"
 #define ERR_FILE_ALREADY_OPEN_W  "Arquivo j� aberto para escrita"
 #define ERR_FILE_ALREADY_OPEN_R  "Arquivo j� aberto para leitura"
 #define ERR_INVALID_REFNUM       "N�mero de refer�ncia"
 #define ERR_GETTING_FILE_POS     "Erro ao tentar obter posi��o do arquivo"
 #define ERR_VOLUME_OFFLINE       "Volume est� indispon�vel"
 #define ERR_PERMISSION_DENIED    "Permiss�o negada"
 #define ERR_VOL_ALREADY_ONLINE   "Volume dispon�vel"
 #define ERR_NO_SUCH_DRIVE        "Drive inexistente"
 #define ERR_NOT_MAC_DISK         "N�o � um disco Macintosh"
 #define ERR_VOL_EXTERNAL_FS      "Volume pertence a um sistema de arquivos externo"
 #define ERR_PROBLEM_RENAME       "Problema durante renomea��o"
 #define ERR_BAD_MASTER_BLOCK     "Bloco master do diret�rio inv�lido"
 #define ERR_CANT_MOVE_FORBIDDEN  "Tentativa de mover proibida"
 #define ERR_WRONG_VOL_TYPE       "Tipo inv�lido de volume"
 #define ERR_SERVER_VOL_LOST      "Volume servidor desconectado"
 #define ERR_FILE_ID_NOT_FOUND    "ID de Arquivo n�o encontrado"
 #define ERR_FILE_ID_EXISTS       "ID de Arquivo j� existente"
 #define ERR_SERVER_NO_RESPOND    "Servidor n�o respondendo"
 #define ERR_USER_AUTH_FAILED     "Autentica��o de usu�rio falhada"
 #define ERR_PWORD_EXPIRED        "Password foi expirada no servidor"
 #define ERR_ACCESS_DENIED        "Accesso negado"
 #define ERR_NOT_A_DOS_DISK       "N�o � um disco DOS"
 #define ERR_SHARING_VIOLATION    "Viola��o de compartilhamento"
 #define ERR_CANNOT_MAKE          "N�o pode ser feito"
 #define ERR_DEV_IN_USE           "Device j� em uso"
 #define ERR_OPEN_FAILED          "Falaha na abertura"
 #define ERR_PIPE_BUSY            "Fila ocupada"
 #define ERR_SHARING_BUF_EXCEEDED "Buffer de compartilhamento excedeu"
 #define ERR_TOO_MANY_HANDLES     "Muitos handles abertos"
 #define ERR_SEEK_ERROR           "Erro de posicionamento"
 #define ERR_DEL_CWD              "Tentando remover diret�rio de trabalho atual"
 #define ERR_WRITE_PROTECT_ERROR  "Erro de prote��o de escrita"
 #define ERR_WRITE_FAULT          "Erro de escrita"
 #define ERR_LOCK_VIOLATION       "Viola��o de trava"
 #define ERR_GEN_FAILURE          "Falha geral"
 #define ERR_UNCERTAIN_MEDIA      "Media incerta"
 #define ERR_PROT_VIOLATION       "Viola��o de prote��o"
 #define ERR_BROKEN_PIPE          "Fila quebrada"

#elif (PHYSFS_LANG == PHYSFS_LANG_SPANISH)
 #define DIR_ARCHIVE_DESCRIPTION  "No es un archivo, E/S directa al sistema de ficheros"
 #define GRP_ARCHIVE_DESCRIPTION  "Formato Build engine Groupfile"
 #define HOG_ARCHIVE_DESCRIPTION  "Formato Descent I/II HOG file"
 #define MVL_ARCHIVE_DESCRIPTION  "Formato Descent II Movielib"
 #define QPAK_ARCHIVE_DESCRIPTION "Formato Quake I/II"
 #define ZIP_ARCHIVE_DESCRIPTION  "Compatible con PkZip/WinZip/Info-Zip"
 #define WAD_ARCHIVE_DESCRIPTION  "DOOM engine format" /* !!! FIXME: translate this line if needed */
 #define LZMA_ARCHIVE_DESCRIPTION "LZMA (7zip) format" /* !!! FIXME: translate this line if needed */

 #define ERR_IS_INITIALIZED       "Ya estaba inicializado"
 #define ERR_NOT_INITIALIZED      "No est� inicializado"
 #define ERR_INVALID_ARGUMENT     "Argumento inv�lido"
 #define ERR_FILES_STILL_OPEN     "Archivos a�n abiertos"
 #define ERR_NO_DIR_CREATE        "Fallo al crear los directorios"
 #define ERR_OUT_OF_MEMORY        "Memoria agotada"
 #define ERR_NOT_IN_SEARCH_PATH   "No existe tal entrada en la ruta de b�squeda"
 #define ERR_NOT_SUPPORTED        "Operaci�n no soportada"
 #define ERR_UNSUPPORTED_ARCHIVE  "Tipo de archivo no soportado"
 #define ERR_NOT_A_HANDLE         "No es un manejador de ficheo (file handle)"
 #define ERR_INSECURE_FNAME       "Nombre de archivo inseguro"
 #define ERR_SYMLINK_DISALLOWED   "Los enlaces simb�licos est�n desactivados"
 #define ERR_NO_WRITE_DIR         "No has configurado un directorio de escritura"
 #define ERR_NO_SUCH_FILE         "Archivo no encontrado"
 #define ERR_NO_SUCH_PATH         "Ruta no encontrada"
 #define ERR_NO_SUCH_VOLUME       "Volumen no encontrado"
 #define ERR_PAST_EOF             "Te pasaste del final del archivo"
 #define ERR_ARC_IS_READ_ONLY     "El archivo es de s�lo lectura"
 #define ERR_IO_ERROR             "Error E/S"
 #define ERR_CANT_SET_WRITE_DIR   "No puedo configurar el directorio de escritura"
 #define ERR_SYMLINK_LOOP         "Bucle infnito de enlaces simb�licos"
 #define ERR_COMPRESSION          "Error de (des)compresi�n"
 #define ERR_NOT_IMPLEMENTED      "No implementado"
 #define ERR_OS_ERROR             "El sistema operativo ha devuelto un error"
 #define ERR_FILE_EXISTS          "El archivo ya existe"
 #define ERR_NOT_A_FILE           "No es un archivo"
 #define ERR_NOT_A_DIR            "No es un directorio"
 #define ERR_NOT_AN_ARCHIVE       "No es un archivo"
 #define ERR_CORRUPTED            "Archivo corrupto"
 #define ERR_SEEK_OUT_OF_RANGE    "B�squeda fuera de rango"
 #define ERR_BAD_FILENAME         "Nombre de archivo incorrecto"
 #define ERR_PHYSFS_BAD_OS_CALL   "(BUG) PhysicsFS ha hecho una llamada incorrecta al sistema"
 #define ERR_ARGV0_IS_NULL        "argv0 es NULL"
 #define ERR_NEED_DICT            "necesito diccionario"
 #define ERR_DATA_ERROR           "error de datos"
 #define ERR_MEMORY_ERROR         "error de memoria"
 #define ERR_BUFFER_ERROR         "error de buffer"
 #define ERR_VERSION_ERROR        "error de versi�n"
 #define ERR_UNKNOWN_ERROR        "error desconocido"
 #define ERR_SEARCHPATH_TRUNC     "La ruta de b�squeda ha sido truncada"
 #define ERR_GETMODFN_TRUNC       "GetModuleFileName() ha sido truncado"
 #define ERR_GETMODFN_NO_DIR      "GetModuleFileName() no tenia directorio"
 #define ERR_DISK_FULL            "El disco est� lleno"
 #define ERR_DIRECTORY_FULL       "El directorio est� lleno"
 #define ERR_MACOS_GENERIC        "MacOS ha devuelto un error (%d)"
 #define ERR_OS2_GENERIC          "OS/2 ha devuelto un error (%d)"
 #define ERR_VOL_LOCKED_HW        "El volumen est� bloqueado por el hardware"
 #define ERR_VOL_LOCKED_SW        "El volumen est� bloqueado por el software"
 #define ERR_FILE_LOCKED          "El archivo est� bloqueado"
 #define ERR_FILE_OR_DIR_BUSY     "Fichero o directorio ocupados"
 #define ERR_FILE_ALREADY_OPEN_W  "Fichero ya abierto para escritura"
 #define ERR_FILE_ALREADY_OPEN_R  "Fichero ya abierto para lectura"
 #define ERR_INVALID_REFNUM       "El n�mero de referencia no es v�lido"
 #define ERR_GETTING_FILE_POS     "Error al tomar la posici�n del fichero"
 #define ERR_VOLUME_OFFLINE       "El volumen est� desconectado"
 #define ERR_PERMISSION_DENIED    "Permiso denegado"
 #define ERR_VOL_ALREADY_ONLINE   "El volumen ya estaba conectado"
 #define ERR_NO_SUCH_DRIVE        "No existe tal unidad"
 #define ERR_NOT_MAC_DISK         "No es un disco Macintosh"
 #define ERR_VOL_EXTERNAL_FS      "El volumen pertence a un sistema de ficheros externo"
 #define ERR_PROBLEM_RENAME       "Problemas al renombrar"
 #define ERR_BAD_MASTER_BLOCK     "Bloque maestro de directorios incorrecto"
 #define ERR_CANT_MOVE_FORBIDDEN  "Intento de mover forbidden"
 #define ERR_WRONG_VOL_TYPE       "Tipo de volumen incorrecto"
 #define ERR_SERVER_VOL_LOST      "El servidor de vol�menes ha sido desconectado"
 #define ERR_FILE_ID_NOT_FOUND    "Identificador de archivo no encontrado"
 #define ERR_FILE_ID_EXISTS       "El identificador de archivo ya existe"
 #define ERR_SERVER_NO_RESPOND    "El servidor no responde"
 #define ERR_USER_AUTH_FAILED     "Fallo al autentificar el usuario"
 #define ERR_PWORD_EXPIRED        "La Password  en el servidor ha caducado"
 #define ERR_ACCESS_DENIED        "Acceso denegado"
 #define ERR_NOT_A_DOS_DISK       "No es un disco de DOS"
 #define ERR_SHARING_VIOLATION    "Violaci�n al compartir"
 #define ERR_CANNOT_MAKE          "No puedo hacer make"
 #define ERR_DEV_IN_USE           "El dispositivo ya estaba en uso"
 #define ERR_OPEN_FAILED          "Fallo al abrir"
 #define ERR_PIPE_BUSY            "Tuber�a ocupada"
 #define ERR_SHARING_BUF_EXCEEDED "Buffer de compartici�n sobrepasado"
 #define ERR_TOO_MANY_HANDLES     "Demasiados manejadores (handles)"
 #define ERR_SEEK_ERROR           "Error de b�squeda"
 #define ERR_DEL_CWD              "Intentando borrar el directorio de trabajo actual"
 #define ERR_WRITE_PROTECT_ERROR  "Error de protecci�n contra escritura"
 #define ERR_WRITE_FAULT          "Fallo al escribir"
 #define ERR_LOCK_VIOLATION       "Violaci�n del bloqueo"
 #define ERR_GEN_FAILURE          "Fallo general"
 #define ERR_UNCERTAIN_MEDIA      "Medio incierto"
 #define ERR_PROT_VIOLATION       "Violaci�n de la protecci�n"
 #define ERR_BROKEN_PIPE          "Tuber�a rota"

#else
 #error Please define PHYSFS_LANG.
#endif

/* end LANG section. */

struct __PHYSFS_DIRHANDLE__;
struct __PHYSFS_FILEFUNCTIONS__;


/* !!! FIXME: find something better than "dvoid" and "fvoid" ... */
/* Opaque data for file and dir handlers... */
typedef void dvoid;
typedef void fvoid;


typedef struct
{
        /*
         * Basic info about this archiver...
         */
    const PHYSFS_ArchiveInfo *info;


    /*
     * DIRECTORY ROUTINES:
     * These functions are for dir handles. Generate a handle with the
     *  openArchive() method, then pass it as the "opaque" dvoid to the
     *  others.
     *
     * Symlinks should always be followed; PhysicsFS will use the
     *  isSymLink() method and make a judgement on whether to
     *  continue to call other methods based on that.
     */


        /*
         * Returns non-zero if (filename) is a valid archive that this
         *  driver can handle. This filename is in platform-dependent
         *  notation. forWriting is non-zero if this is to be used for
         *  the write directory, and zero if this is to be used for an
         *  element of the search path.
         */
    int (*isArchive)(const char *filename, int forWriting);

        /*
         * Open a dirhandle for dir/archive (name).
         *  This filename is in platform-dependent notation.
         *  forWriting is non-zero if this is to be used for
         *  the write directory, and zero if this is to be used for an
         *  element of the search path.
         * Returns NULL on failure, and calls __PHYSFS_setError().
         *  Returns non-NULL on success. The pointer returned will be
         *  passed as the "opaque" parameter for later calls.
         */
    void *(*openArchive)(const char *name, int forWriting);

        /*
         * List all files in (dirname). Each file is passed to (callback),
         *  where a copy is made if appropriate, so you should dispose of
         *  it properly upon return from the callback.
         * You should omit symlinks if (omitSymLinks) is non-zero.
         * If you have a failure, report as much as you can.
         *  (dirname) is in platform-independent notation.
         */
    void (*enumerateFiles)(dvoid *opaque,
                            const char *dirname,
                            int omitSymLinks,
                            PHYSFS_EnumFilesCallback callback,
                            const char *origdir,
                            void *callbackdata);

        /*
         * Returns non-zero if filename can be opened for reading.
         *  This filename is in platform-independent notation.
         *  You should not follow symlinks.
         */
    int (*exists)(dvoid *opaque, const char *name);

        /*
         * Returns non-zero if filename is really a directory.
         *  This filename is in platform-independent notation.
         *  Symlinks should be followed; if what the symlink points
         *  to is missing, or isn't a directory, then the retval is zero.
         *
         * Regardless of success or failure, please set *fileExists to
         *  non-zero if the file existed (even if it's a broken symlink!),
         *  zero if it did not.
         */
    int (*isDirectory)(dvoid *opaque, const char *name, int *fileExists);

        /*
         * Returns non-zero if filename is really a symlink.
         *  This filename is in platform-independent notation.
         *
         * Regardless of success or failure, please set *fileExists to
         *  non-zero if the file existed (even if it's a broken symlink!),
         *  zero if it did not.
         */
    int (*isSymLink)(dvoid *opaque, const char *name, int *fileExists);

        /*
         * Retrieve the last modification time (mtime) of a file.
         *  Returns -1 on failure, or the file's mtime in seconds since
         *  the epoch (Jan 1, 1970) on success.
         *  This filename is in platform-independent notation.
         *
         * Regardless of success or failure, please set *exists to
         *  non-zero if the file existed (even if it's a broken symlink!),
         *  zero if it did not.
         */
    PHYSFS_sint64 (*getLastModTime)(dvoid *opaque, const char *fnm, int *exist);

        /*
         * Open file for reading.
         *  This filename is in platform-independent notation.
         * If you can't handle multiple opens of the same file,
         *  you can opt to fail for the second call.
         * Fail if the file does not exist.
         * Returns NULL on failure, and calls __PHYSFS_setError().
         *  Returns non-NULL on success. The pointer returned will be
         *  passed as the "opaque" parameter for later file calls.
         *
         * Regardless of success or failure, please set *fileExists to
         *  non-zero if the file existed (even if it's a broken symlink!),
         *  zero if it did not.
         */
    fvoid *(*openRead)(dvoid *opaque, const char *fname, int *fileExists);

        /*
         * Open file for writing.
         * If the file does not exist, it should be created. If it exists,
         *  it should be truncated to zero bytes. The writing
         *  offset should be the start of the file.
         * This filename is in platform-independent notation.
         * If you can't handle multiple opens of the same file,
         *  you can opt to fail for the second call.
         * Returns NULL on failure, and calls __PHYSFS_setError().
         *  Returns non-NULL on success. The pointer returned will be
         *  passed as the "opaque" parameter for later file calls.
         */
    fvoid *(*openWrite)(dvoid *opaque, const char *filename);

        /*
         * Open file for appending.
         * If the file does not exist, it should be created. The writing
         *  offset should be the end of the file.
         * This filename is in platform-independent notation.
         * If you can't handle multiple opens of the same file,
         *  you can opt to fail for the second call.
         * Returns NULL on failure, and calls __PHYSFS_setError().
         *  Returns non-NULL on success. The pointer returned will be
         *  passed as the "opaque" parameter for later file calls.
         */
    fvoid *(*openAppend)(dvoid *opaque, const char *filename);

        /*
         * Delete a file in the archive/directory.
         *  Return non-zero on success, zero on failure.
         *  This filename is in platform-independent notation.
         *  This method may be NULL.
         * On failure, call __PHYSFS_setError().
         */
    int (*remove)(dvoid *opaque, const char *filename);

        /*
         * Create a directory in the archive/directory.
         *  If the application is trying to make multiple dirs, PhysicsFS
         *  will split them up into multiple calls before passing them to
         *  your driver.
         *  Return non-zero on success, zero on failure.
         *  This filename is in platform-independent notation.
         *  This method may be NULL.
         * On failure, call __PHYSFS_setError().
         */
    int (*mkdir)(dvoid *opaque, const char *filename);

        /*
         * Close directories/archives, and free any associated memory,
         *  including (opaque) itself if applicable. Implementation can assume
         *  that it won't be called if there are still files open from
         *  this archive.
         */
    void (*dirClose)(dvoid *opaque);



    /*
     * FILE ROUTINES:
     * These functions are for file handles generated by the open*() methods.
     *  They are distinguished by taking a "fvoid" instead of a "dvoid" for
     *  the opaque handle.
     */

        /*
         * Read more from the file.
         * Returns number of objects of (objSize) bytes read from file, -1
         *  if complete failure.
         * On failure, call __PHYSFS_setError().
         */
    PHYSFS_sint64 (*read)(fvoid *opaque, void *buffer,
                          PHYSFS_uint32 objSize, PHYSFS_uint32 objCount);

        /*
         * Write more to the file. Archives don't have to implement this.
         *  (Set it to NULL if not implemented).
         * Returns number of objects of (objSize) bytes written to file, -1
         *  if complete failure.
         * On failure, call __PHYSFS_setError().
         */
    PHYSFS_sint64 (*write)(fvoid *opaque, const void *buffer,
                 PHYSFS_uint32 objSize, PHYSFS_uint32 objCount);

        /*
         * Returns non-zero if at end of file.
         */
    int (*eof)(fvoid *opaque);

        /*
         * Returns byte offset from start of file.
         */
    PHYSFS_sint64 (*tell)(fvoid *opaque);

        /*
         * Move read/write pointer to byte offset from start of file.
         *  Returns non-zero on success, zero on error.
         * On failure, call __PHYSFS_setError().
         */
    int (*seek)(fvoid *opaque, PHYSFS_uint64 offset);

        /*
         * Return number of bytes available in the file, or -1 if you
         *  aren't able to determine.
         * On failure, call __PHYSFS_setError().
         */
    PHYSFS_sint64 (*fileLength)(fvoid *opaque);

        /*
         * Close the file, and free associated resources, including (opaque)
         *  if applicable. Returns non-zero on success, zero if can't close
         *  file. On failure, call __PHYSFS_setError().
         */
    int (*fileClose)(fvoid *opaque);
} PHYSFS_Archiver;


/*
 * Call this to set the message returned by PHYSFS_getLastError().
 *  Please only use the ERR_* constants above, or add new constants to the
 *  above group, but I want these all in one place.
 *
 * Calling this with a NULL argument is a safe no-op.
 */
void __PHYSFS_setError(const char *err);


/*
 * Convert (dirName) to platform-dependent notation, then prepend (prepend)
 *  and append (append) to the converted string.
 *
 *  So, on Win32, calling:
 *     __PHYSFS_convertToDependent("C:\", "my/files", NULL);
 *  ...will return the string "C:\my\files".
 *
 * This is a convenience function; you might want to hack something out that
 *  is less generic (and therefore more efficient).
 *
 * Be sure to free() the return value when done with it.
 */
char *__PHYSFS_convertToDependent(const char *prepend,
                                  const char *dirName,
                                  const char *append);


/* This byteorder stuff was lifted from SDL. http://www.libsdl.org/ */
#define PHYSFS_LIL_ENDIAN  1234
#define PHYSFS_BIG_ENDIAN  4321

#if  defined(__i386__) || defined(__ia64__) || defined(WIN32) || \
    (defined(__alpha__) || defined(__alpha)) || \
     defined(__arm__) || defined(ARM) || \
    (defined(__mips__) && defined(__MIPSEL__)) || \
     defined(__SYMBIAN32__) || \
     defined(__x86_64__) || \
     defined(__LITTLE_ENDIAN__)
#define PHYSFS_BYTEORDER    PHYSFS_LIL_ENDIAN
#else
#define PHYSFS_BYTEORDER    PHYSFS_BIG_ENDIAN
#endif


/*
 * When sorting the entries in an archive, we use a modified QuickSort.
 *  When there are less then PHYSFS_QUICKSORT_THRESHOLD entries left to sort,
 *  we switch over to a BubbleSort for the remainder. Tweak to taste.
 *
 * You can override this setting by defining PHYSFS_QUICKSORT_THRESHOLD
 *  before #including "physfs_internal.h".
 */
#ifndef PHYSFS_QUICKSORT_THRESHOLD
#define PHYSFS_QUICKSORT_THRESHOLD 4
#endif

/*
 * Sort an array (or whatever) of (max) elements. This uses a mixture of
 *  a QuickSort and BubbleSort internally.
 * (cmpfn) is used to determine ordering, and (swapfn) does the actual
 *  swapping of elements in the list.
 *
 *  See zip.c for an example.
 */
void __PHYSFS_sort(void *entries, PHYSFS_uint32 max,
                   int (*cmpfn)(void *, PHYSFS_uint32, PHYSFS_uint32),
                   void (*swapfn)(void *, PHYSFS_uint32, PHYSFS_uint32));


/* These get used all over for lessening code clutter. */
#define BAIL_MACRO(e, r) { __PHYSFS_setError(e); return r; }
#define BAIL_IF_MACRO(c, e, r) if (c) { __PHYSFS_setError(e); return r; }
#define BAIL_MACRO_MUTEX(e, m, r) { __PHYSFS_setError(e); __PHYSFS_platformReleaseMutex(m); return r; }
#define BAIL_IF_MACRO_MUTEX(c, e, m, r) if (c) { __PHYSFS_setError(e); __PHYSFS_platformReleaseMutex(m); return r; }
#define GOTO_MACRO(e, g) { __PHYSFS_setError(e); goto g; }
#define GOTO_IF_MACRO(c, e, g) if (c) { __PHYSFS_setError(e); goto g; }
#define GOTO_MACRO_MUTEX(e, m, g) { __PHYSFS_setError(e); __PHYSFS_platformReleaseMutex(m); goto g; }
#define GOTO_IF_MACRO_MUTEX(c, e, m, g) if (c) { __PHYSFS_setError(e); __PHYSFS_platformReleaseMutex(m); goto g; }

#define __PHYSFS_ARRAYLEN(x) ( (sizeof (x)) / (sizeof (x[0])) )

#if (defined __GNUC__)
#define __PHYSFS_SI64(x) x##LL
#define __PHYSFS_UI64(x) x##ULL
#elif (defined _MSC_VER)
#define __PHYSFS_SI64(x) x##i64
#define __PHYSFS_UI64(x) x##ui64
#else
#define __PHYSFS_SI64(x) x
#define __PHYSFS_UI64(x) x
#endif

/*
 * Check if a ui64 will fit in the platform's address space.
 *  The initial sizeof check will optimize this macro out entirely on
 *  64-bit (and larger?!) platforms, and the other condition will
 *  return zero or non-zero if the variable will fit in the platform's
 *  size_t, suitable to pass to malloc. This is kinda messy, but effective.
 */
#define __PHYSFS_ui64FitsAddressSpace(s) ( \
    (sizeof (PHYSFS_uint64) > sizeof (size_t)) && \
    ((s) > (__PHYSFS_UI64(0xFFFFFFFFFFFFFFFF) >> (64-(sizeof(size_t)*8)))) \
)

/*
 * This is a strcasecmp() or stricmp() replacement that expects both strings
 *  to be in UTF-8 encoding. It will do "case folding" to decide if the
 *  Unicode codepoints in the strings match.
 *
 * It will report which string is "greater than" the other, but be aware that
 *  this doesn't necessarily mean anything: 'a' may be "less than" 'b', but
 *  a random Kanji codepoint has no meaningful alphabetically relationship to
 *  a Greek Lambda, but being able to assign a reliable "value" makes sorting
 *  algorithms possible, if not entirely sane. Most cases should treat the
 *  return value as "equal" or "not equal".
 */
int __PHYSFS_utf8strcasecmp(const char *s1, const char *s2);

/*
 * This works like __PHYSFS_utf8strcasecmp(), but takes a character (NOT BYTE
 *  COUNT) argument, like strcasencmp().
 */
int __PHYSFS_utf8strnicmp(const char *s1, const char *s2, PHYSFS_uint32 l);

/*
 * stricmp() that guarantees to only work with low ASCII. The C runtime
 *  stricmp() might try to apply a locale/codepage/etc, which we don't want.
 */
int __PHYSFS_stricmpASCII(const char *s1, const char *s2);

/*
 * strnicmp() that guarantees to only work with low ASCII. The C runtime
 *  strnicmp() might try to apply a locale/codepage/etc, which we don't want.
 */
int __PHYSFS_strnicmpASCII(const char *s1, const char *s2, PHYSFS_uint32 l);


/*
 * The current allocator. Not valid before PHYSFS_init is called!
 */
extern PHYSFS_Allocator __PHYSFS_AllocatorHooks;

/* convenience macro to make this less cumbersome internally... */
#define allocator __PHYSFS_AllocatorHooks

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
/*------------                                              ----------------*/
/*------------  You MUST implement the following functions  ----------------*/
/*------------        if porting to a new platform.         ----------------*/
/*------------     (see platform/unix.c for an example)     ----------------*/
/*------------                                              ----------------*/
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/


/*
 * The dir separator; "/" on unix, "\\" on win32, ":" on MacOS, etc...
 *  Obviously, this isn't a function, but it IS a null-terminated string.
 */
extern const char *__PHYSFS_platformDirSeparator;


/*
 * Initialize the platform. This is called when PHYSFS_init() is called from
 *  the application. You can use this to (for example) determine what version
 *  of Windows you're running.
 *
 * Return zero if there was a catastrophic failure (which prevents you from
 *  functioning at all), and non-zero otherwise.
 */
int __PHYSFS_platformInit(void);


/*
 * Deinitialize the platform. This is called when PHYSFS_deinit() is called
 *  from the application. You can use this to clean up anything you've
 *  allocated in your platform driver.
 *
 * Return zero if there was a catastrophic failure (which prevents you from
 *  functioning at all), and non-zero otherwise.
 */
int __PHYSFS_platformDeinit(void);


/*
 * Open a file for reading. (filename) is in platform-dependent notation. The
 *  file pointer should be positioned on the first byte of the file.
 *
 * The return value will be some platform-specific datatype that is opaque to
 *  the caller; it could be a (FILE *) under Unix, or a (HANDLE *) under win32.
 *
 * The same file can be opened for read multiple times, and each should have
 *  a unique file handle; this is frequently employed to prevent race
 *  conditions in the archivers.
 *
 * Call __PHYSFS_setError() and return (NULL) if the file can't be opened.
 */
void *__PHYSFS_platformOpenRead(const char *filename);


/*
 * Open a file for writing. (filename) is in platform-dependent notation. If
 *  the file exists, it should be truncated to zero bytes, and if it doesn't
 *  exist, it should be created as a zero-byte file. The file pointer should
 *  be positioned on the first byte of the file.
 *
 * The return value will be some platform-specific datatype that is opaque to
 *  the caller; it could be a (FILE *) under Unix, or a (HANDLE *) under win32,
 *  etc.
 *
 * Opening a file for write multiple times has undefined results.
 *
 * Call __PHYSFS_setError() and return (NULL) if the file can't be opened.
 */
void *__PHYSFS_platformOpenWrite(const char *filename);


/*
 * Open a file for appending. (filename) is in platform-dependent notation. If
 *  the file exists, the file pointer should be place just past the end of the
 *  file, so that the first write will be one byte after the current end of
 *  the file. If the file doesn't exist, it should be created as a zero-byte
 *  file. The file pointer should be positioned on the first byte of the file.
 *
 * The return value will be some platform-specific datatype that is opaque to
 *  the caller; it could be a (FILE *) under Unix, or a (HANDLE *) under win32,
 *  etc.
 *
 * Opening a file for append multiple times has undefined results.
 *
 * Call __PHYSFS_setError() and return (NULL) if the file can't be opened.
 */
void *__PHYSFS_platformOpenAppend(const char *filename);


/*
 * Read more data from a platform-specific file handle. (opaque) should be
 *  cast to whatever data type your platform uses. Read a maximum of (count)
 *  objects of (size) 8-bit bytes to the area pointed to by (buffer). If there
 *  isn't enough data available, return the number of full objects read, and
 *  position the file pointer at the start of the first incomplete object.
 *  On success, return (count) and position the file pointer one byte past
 *  the end of the last read object. Return (-1) if there is a catastrophic
 *  error, and call __PHYSFS_setError() to describe the problem; the file
 *  pointer should not move in such a case.
 */
PHYSFS_sint64 __PHYSFS_platformRead(void *opaque, void *buffer,
                                    PHYSFS_uint32 size, PHYSFS_uint32 count);

/*
 * Write more data to a platform-specific file handle. (opaque) should be
 *  cast to whatever data type your platform uses. Write a maximum of (count)
 *  objects of (size) 8-bit bytes from the area pointed to by (buffer). If
 *  there isn't enough data available, return the number of full objects
 *  written, and position the file pointer at the start of the first
 *  incomplete object. Return (-1) if there is a catastrophic error, and call
 *  __PHYSFS_setError() to describe the problem; the file pointer should not
 *  move in such a case.
 */
PHYSFS_sint64 __PHYSFS_platformWrite(void *opaque, const void *buffer,
                                     PHYSFS_uint32 size, PHYSFS_uint32 count);

/*
 * Set the file pointer to a new position. (opaque) should be cast to
 *  whatever data type your platform uses. (pos) specifies the number
 *  of 8-bit bytes to seek to from the start of the file. Seeking past the
 *  end of the file is an error condition, and you should check for it.
 *
 * Not all file types can seek; this is to be expected by the caller.
 *
 * On error, call __PHYSFS_setError() and return zero. On success, return
 *  a non-zero value.
 */
int __PHYSFS_platformSeek(void *opaque, PHYSFS_uint64 pos);


/*
 * Get the file pointer's position, in an 8-bit byte offset from the start of
 *  the file. (opaque) should be cast to whatever data type your platform
 *  uses.
 *
 * Not all file types can "tell"; this is to be expected by the caller.
 *
 * On error, call __PHYSFS_setError() and return zero. On success, return
 *  a non-zero value.
 */
PHYSFS_sint64 __PHYSFS_platformTell(void *opaque);


/*
 * Determine the current size of a file, in 8-bit bytes, from an open file.
 *
 * The caller expects that this information may not be available for all
 *  file types on all platforms.
 *
 * Return -1 if you can't do it, and call __PHYSFS_setError(). Otherwise,
 *  return the file length in 8-bit bytes.
 */
PHYSFS_sint64 __PHYSFS_platformFileLength(void *handle);

/*
 * Determine if a file is at EOF. (opaque) should be cast to whatever data
 *  type your platform uses.
 *
 * The caller expects that there was a short read before calling this.
 *
 * Return non-zero if EOF, zero if it is _not_ EOF.
 */
int __PHYSFS_platformEOF(void *opaque);

/*
 * Flush any pending writes to disk. (opaque) should be cast to whatever data
 *  type your platform uses. Be sure to check for errors; the caller expects
 *  that this function can fail if there was a flushing error, etc.
 *
 *  Return zero on failure, non-zero on success.
 */
int __PHYSFS_platformFlush(void *opaque);

/*
 * Flush and close a file. (opaque) should be cast to whatever data type
 *  your platform uses. Be sure to check for errors when closing; the
 *  caller expects that this function can fail if there was a flushing
 *  error, etc.
 *
 * You should clean up all resources associated with (opaque).
 *
 *  Return zero on failure, non-zero on success.
 */
int __PHYSFS_platformClose(void *opaque);

/*
 * Platform implementation of PHYSFS_getCdRomDirsCallback()...
 *  CD directories are discovered and reported to the callback one at a time.
 *  Pointers passed to the callback are assumed to be invalid to the
 *  application after the callback returns, so you can free them or whatever.
 *  Callback does not assume results will be sorted in any meaningful way.
 */
void __PHYSFS_platformDetectAvailableCDs(PHYSFS_StringCallback cb, void *data);

/*
 * Calculate the base dir, if your platform needs special consideration.
 *  Just return NULL if the standard routines will suffice. (see
 *  calculateBaseDir() in physfs.c ...)
 *  Caller will free() the retval if it's not NULL.
 */
char *__PHYSFS_platformCalcBaseDir(const char *argv0);

/*
 * Get the platform-specific user name.
 *  Caller will free() the retval if it's not NULL. If it's NULL, the username
 *  will default to "default".
 */
char *__PHYSFS_platformGetUserName(void);

/*
 * Get the platform-specific user dir.
 *  Caller will free() the retval if it's not NULL. If it's NULL, the userdir
 *  will default to basedir/username.
 */
char *__PHYSFS_platformGetUserDir(void);

/*
 * Return a number that uniquely identifies the current thread.
 *  On a platform without threading, (1) will suffice. These numbers are
 *  arbitrary; the only requirement is that no two threads have the same
 *  number.
 */
PHYSFS_uint64 __PHYSFS_platformGetThreadID(void);

/*
 * Return non-zero if filename (in platform-dependent notation) exists.
 *  Symlinks should NOT be followed; at this stage, we do not care what the
 *  symlink points to. Please call __PHYSFS_SetError() with the details of
 *  why the file does not exist, if it doesn't; you are in a better position
 *  to know (path not found, bogus filename, file itself is missing, etc).
 */
int __PHYSFS_platformExists(const char *fname);

/*
 * Return the last modified time (in seconds since the epoch) of a file.
 *  Returns -1 on failure. (fname) is in platform-dependent notation.
 *  Symlinks should be followed; if what the symlink points to is missing,
 *  then the retval is -1.
 */
PHYSFS_sint64 __PHYSFS_platformGetLastModTime(const char *fname);

/*
 * Return non-zero if filename (in platform-dependent notation) is a symlink.
 */
int __PHYSFS_platformIsSymLink(const char *fname);


/*
 * Return non-zero if filename (in platform-dependent notation) is a symlink.
 *  Symlinks should be followed; if what the symlink points to is missing,
 *  or isn't a directory, then the retval is false.
 */
int __PHYSFS_platformIsDirectory(const char *fname);


/*
 * Convert (dirName) to platform-dependent notation, then prepend (prepend)
 *  and append (append) to the converted string.
 *
 *  So, on Win32, calling:
 *     __PHYSFS_platformCvtToDependent("C:\", "my/files", NULL);
 *  ...will return the string "C:\my\files".
 *
 * This can be implemented in a platform-specific manner, so you can get
 *  get a speed boost that the default implementation can't, since
 *  you can make assumptions about the size of strings, etc..
 *
 * Platforms that choose not to implement this may just call
 *  __PHYSFS_convertToDependent() as a passthrough, which may fit the bill
 *  already.
 *
 * Be sure to free() the return value when done with it.
 */
char *__PHYSFS_platformCvtToDependent(const char *prepend,
                                      const char *dirName,
                                      const char *append);


/*
 * Enumerate a directory of files. This follows the rules for the
 *  PHYSFS_Archiver->enumerateFiles() method (see above), except that the
 *  (dirName) that is passed to this function is converted to
 *  platform-DEPENDENT notation by the caller. The PHYSFS_Archiver version
 *  uses platform-independent notation. Note that ".", "..", and other
 *  metaentries should always be ignored.
 */
void __PHYSFS_platformEnumerateFiles(const char *dirname,
                                     int omitSymLinks,
                                     PHYSFS_EnumFilesCallback callback,
                                     const char *origdir,
                                     void *callbackdata);


/*
 * Get the current working directory. The return value should be an
 *  absolute path in platform-dependent notation. The caller will deallocate
 *  the return value with the standard C runtime free() function when it
 *  is done with it.
 * On error, return NULL and set the error message.
 */
char *__PHYSFS_platformCurrentDir(void);


/*
 * Get the real physical path to a file. (path) is specified in
 *  platform-dependent notation, as should your return value be.
 *  All relative paths should be removed, leaving you with an absolute
 *  path. Symlinks should be resolved, too, so that the returned value is
 *  the most direct path to a file.
 * The return value will be deallocated with the standard C runtime free()
 *  function when the caller is done with it.
 * On error, return NULL and set the error message.
 */
char *__PHYSFS_platformRealPath(const char *path);


/*
 * Make a directory in the actual filesystem. (path) is specified in
 *  platform-dependent notation. On error, return zero and set the error
 *  message. Return non-zero on success.
 */
int __PHYSFS_platformMkDir(const char *path);


/*
 * Remove a file or directory entry in the actual filesystem. (path) is
 *  specified in platform-dependent notation. Note that this deletes files
 *  _and_ directories, so you might need to do some determination.
 *  Non-empty directories should report an error and not delete themselves
 *  or their contents.
 *
 * Deleting a symlink should remove the link, not what it points to.
 *
 * On error, return zero and set the error message. Return non-zero on success.
 */
int __PHYSFS_platformDelete(const char *path);


/*
 * Create a platform-specific mutex. This can be whatever datatype your
 *  platform uses for mutexes, but it is cast to a (void *) for abstractness.
 *
 * Return (NULL) if you couldn't create one. Systems without threads can
 *  return any arbitrary non-NULL value.
 */
void *__PHYSFS_platformCreateMutex(void);

/*
 * Destroy a platform-specific mutex, and clean up any resources associated
 *  with it. (mutex) is a value previously returned by
 *  __PHYSFS_platformCreateMutex(). This can be a no-op on single-threaded
 *  platforms.
 */
void __PHYSFS_platformDestroyMutex(void *mutex);

/*
 * Grab possession of a platform-specific mutex. Mutexes should be recursive;
 *  that is, the same thread should be able to call this function multiple
 *  times in a row without causing a deadlock. This function should block 
 *  until a thread can gain possession of the mutex.
 *
 * Return non-zero if the mutex was grabbed, zero if there was an 
 *  unrecoverable problem grabbing it (this should not be a matter of 
 *  timing out! We're talking major system errors; block until the mutex 
 *  is available otherwise.)
 *
 * _DO NOT_ call __PHYSFS_setError() in here! Since setError calls this
 *  function, you'll cause an infinite recursion. This means you can't
 *  use the BAIL_*MACRO* macros, either.
 */
int __PHYSFS_platformGrabMutex(void *mutex);

/*
 * Relinquish possession of the mutex when this method has been called 
 *  once for each time that platformGrabMutex was called. Once possession has
 *  been released, the next thread in line to grab the mutex (if any) may
 *  proceed.
 *
 * _DO NOT_ call __PHYSFS_setError() in here! Since setError calls this
 *  function, you'll cause an infinite recursion. This means you can't
 *  use the BAIL_*MACRO* macros, either.
 */
void __PHYSFS_platformReleaseMutex(void *mutex);

/*
 * Called at the start of PHYSFS_init() to prepare the allocator, if the user
 *  hasn't selected their own allocator via PHYSFS_setAllocator().
 *  If the platform has a custom allocator, it should fill in the fields of
 *  (a) with the proper function pointers and return non-zero.
 * If the platform just wants to use malloc()/free()/etc, return zero
 *  immediately and the higher level will handle it. The Init and Deinit
 *  fields of (a) are optional...set them to NULL if you don't need them.
 *  Everything else must be implemented. All rules follow those for
 *  PHYSFS_setAllocator(). If Init isn't NULL, it will be called shortly
 *  after this function returns non-zero.
 */
int __PHYSFS_platformSetDefaultAllocator(PHYSFS_Allocator *a);

#ifdef __cplusplus
}
#endif

#endif

/* end of physfs_internal.h ... */

