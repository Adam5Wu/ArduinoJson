#include "JsonBuffer.h"

#include <new>

#include "JsonValue.h"
#include "Internals/JsonParser.h"
#include "Internals/JsonNode.h"

JsonValue JsonBuffer::createValue()
{
    return JsonValue(createNode());
}

JsonNode* JsonBuffer::createNode()
{
    void* node = allocateNode();
    if (!node) return 0;
        
    return new (node) JsonNode();
}

JsonArray JsonBuffer::parseArray(char* json)
{
    JsonParser parser(this, json);
    return JsonArray(parser.parseAnything());
}

JsonNode *JsonBuffer::createArrayNode()
{
    JsonNode* node = createNode();

    if (node)
        node->setAsArray(this);

    return node;
}

JsonNode *JsonBuffer::createObjectNode()
{
    JsonNode* node = createNode();

    if (node)
        node->setAsObject(this);

    return node;
}

JsonNode *JsonBuffer::createLongNode(long value)
{
    JsonNode* node = createNode();

    if (node)
        node->setAsLong(value);

    return node;
}

JsonNode *JsonBuffer::createDoubleNode(double value, int decimals)
{
    JsonNode* node = createNode();

    if (node)
        node->setAsDouble(value, decimals);

    return node;
}