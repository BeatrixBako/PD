#include <windows.h>
#include <iostream>
#include <winioctl.h>

int main() {
    HANDLE hDevice = CreateFile(
        L"\\\\.\\PhysicalDrive0",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hDevice == INVALID_HANDLE_VALUE) {
        std::cerr << "Error, couldn't open device!" << std::endl;
        return 1;
    }

    DISK_GEOMETRY diskGeometry;
    DWORD bytesReturned;

    if (!DeviceIoControl(
        hDevice,
        IOCTL_DISK_GET_DRIVE_GEOMETRY,
        NULL,
        0,
        &diskGeometry,
        sizeof(diskGeometry),
        &bytesReturned,
        NULL)) {
        std::cerr << "Error reading disc geometry!" << std::endl;
        CloseHandle(hDevice);
        return 1;
    }

    std::cout << "Information regarding SSD:" << std::endl;
    std::cout << "Total number of cylinders: " << diskGeometry.Cylinders.QuadPart << std::endl;
    std::cout << "Total number of tracks per cylinders: " << diskGeometry.TracksPerCylinder << std::endl;
    std::cout << "Total number of sectors per track: " << diskGeometry.SectorsPerTrack << std::endl;
    std::cout << "Total number of sectors: " << diskGeometry.Cylinders.QuadPart * diskGeometry.TracksPerCylinder * diskGeometry.SectorsPerTrack << std::endl;

    CloseHandle(hDevice);
    return 0;
}