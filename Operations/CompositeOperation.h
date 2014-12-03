#ifndef Operations_CompositeOperation_h
#define Operations_CompositeOperation_h

#include <vector>
#include <string>
// #include "boost/shared_ptr.hpp"
#include <json/json.h>
#include "AbstractOperation.h"


namespace Operations {

class CompositeOperation : public AbstractOperation {

 public:

    virtual Json::Value execute();
    virtual AbstractOperation* addChild(AbstractOperation*);
    virtual AbstractOperation* removeChild(AbstractOperation*);
    virtual int getNumChildren();
    virtual Json::Value getExecutionTree();

 public:
    std::vector<AbstractOperation*> child_operations;
};

} /* End of namespace Operations */

#endif // Operations_CompositeOperation_h
