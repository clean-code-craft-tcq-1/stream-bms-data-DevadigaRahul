#include "bms-stream-receiver.h"

int main()
{
    std::string line;
    BMSDataStreamReceiver bmsStreamRxObj;
    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            break;
        }

        bmsStreamRxObj.processInputDataStream(line);

    }
    return 0;
}