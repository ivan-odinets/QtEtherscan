#include "eth_response.h"

#include "./eth_helper.h"

namespace QtEtherscan {

namespace Proxy {

Response::Response() :
    m_id{0},
    m_errorCode{UnknownError}
{}

Response::Response(const QJsonObject& jsonObject) :
    m_jsonRpc  {jsonObject.value("jsonrpc").toString() },
    m_id       {jsonObject.value("id").toInt()         },
    m_errorCode{NoError                                }
{
    if (jsonObject.contains("error")) {
        QJsonObject errorObject = jsonObject.value("error").toObject();

        m_errorCode = errorObject.value("code").toInt();
        m_errorMessage = errorObject.value("message").toString();
    }
}

StringResponse::StringResponse()
{}

StringResponse::StringResponse(const QJsonObject& jsonObject) :
    Response{jsonObject}
{
    if (jsonObject.contains("result"))
        m_result = jsonObject.value("result").toString();
}

IntResponse::IntResponse(int defaultValue) :
    Response(),
    m_result{defaultValue}
{}

IntResponse::IntResponse(const QJsonObject& jsonObject, int defaultValue) :
    Response{jsonObject},
    m_result{defaultValue}
{
    if (jsonObject.contains("result"))
        m_result = Helper::ethStringToInt32(jsonObject.value("result").toString());
}

} // namespace Proxy

} // namespace QtEtherscan
