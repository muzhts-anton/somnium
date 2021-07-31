#include "workflow.h"

namespace workflow {
    DataLevel levelDown(DataLevel level)
    {
        switch(level) {
        case DataLevel::IN_ROOT:
            return DataLevel::IN_BOOK;

        case DataLevel::IN_BOOK:
            return DataLevel::IN_CHAPTER;

        case DataLevel::IN_CHAPTER:
            return DataLevel::IN_SUBSECTION;

        case DataLevel::IN_SUBSECTION:
            return DataLevel::IN_SUBSECTION;
        }
    }

    DataLevel levelUp(DataLevel level)
    {
        switch(level) {
        case DataLevel::IN_ROOT:
            return DataLevel::IN_ROOT;

        case DataLevel::IN_BOOK:
            return DataLevel::IN_ROOT;

        case DataLevel::IN_CHAPTER:
            return DataLevel::IN_BOOK;

        case DataLevel::IN_SUBSECTION:
            return DataLevel::IN_CHAPTER;
        }
    }
}
