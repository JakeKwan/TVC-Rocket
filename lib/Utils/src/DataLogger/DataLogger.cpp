#include "DataLogger.h"

bool DataLogger::begin(const char *filename)
{
    if (!sd.begin(SdioConfig(FIFO_SDIO)))
    {
        return false;
    }

    if (!file.open(filename, O_RDWR | O_CREAT | O_TRUNC))
    {
        return false;
    }

    // Choose for flight duration
    if (!file.preAllocate(4 * 1024 * 1024))
    {
        file.close();
        return false;
    }

    buffer.begin(&file);
    dropped = 0;
    return true;
}

bool DataLogger::push(const LoggedData &record)
{
    const size_t written = buffer.write(
        reinterpret_cast<const uint8_t *>(&record),
        sizeof(record));

    if (written != sizeof(record))
    {
        ++dropped;
        return false;
    }

    Log.trace("pushed;");
    return true;
}

void DataLogger::service()
{
    constexpr size_t SectorSize = 512;

    if (buffer.bytesUsed() < SectorSize || file.isBusy())
    {
        return;
    }

    buffer.writeOut(SectorSize);
    Log.trace("Serviced;");
}

void DataLogger::stop()
{
    buffer.sync();
    file.truncate();
    file.close();
    sd.end();
    Log.trace("stopped;");
}

uint32_t DataLogger::droppedRecords() const
{
    return dropped;
}