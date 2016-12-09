/*
 * Connection.hpp
 *
 * Copyright (C) 2009-16 by RStudio, Inc.
 *
 * Unless you have received this program directly from RStudio pursuant
 * to the terms of a commercial license agreement with RStudio, then
 * this program is licensed to you under the terms of version 3 of the
 * GNU Affero General Public License. This program is distributed WITHOUT
 * ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING THOSE OF NON-INFRINGEMENT,
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE. Please refer to the
 * AGPL (http://www.gnu.org/licenses/agpl-3.0.txt) for more details.
 *
 */

#ifndef SESSION_CONNECTIONS_CONNECTION_HPP
#define SESSION_CONNECTIONS_CONNECTION_HPP
 
#include <string>

#include <core/json/Json.hpp>

namespace rstudio {
namespace session {
namespace modules { 
namespace connections {
   
struct ConnectionId
{
   ConnectionId() {}

   ConnectionId(const std::string& type, const std::string& host)
      : type(type), host(host)
   {
   }

   bool empty() const { return type.empty(); }

   std::string type;
   std::string host;

   bool operator==(const ConnectionId& other) const
   {
      return other.type == type && other.host == host;
   }

   bool operator<(const ConnectionId& other) const
   {
      return (other.type + other.host) < (type + host);
   }
};

struct ConnectionAction
{
   ConnectionAction() {}
   ConnectionAction(const std::string& name, const std::string& icon)
      : name(name), icon(icon)
   {
   }

   std::string name;
   std::string icon;
};

struct Connection
{
   Connection() {}
   Connection(const ConnectionId& id,
              const std::string& connectCode,
              const std::string& displayName,
              const std::vector<ConnectionAction>& actions,
              double lastUsed)
      : id(id),
        connectCode(connectCode),
        displayName(displayName),
        actions(actions),
        lastUsed(lastUsed)
   {
   }

   bool empty() const { return id.empty(); }

   ConnectionId id;
   std::string connectCode;
   std::string displayName;
   std::vector<ConnectionAction> actions;
   double lastUsed;
};

core::json::Object connectionIdJson(const ConnectionId& id);
core::json::Object connectionJson(const Connection& connection);

core::Error connectionFromJson(const core::json::Object& connectionJson,
                               Connection* pConnection);

bool hasConnectionId(const ConnectionId& id,
                     const core::json::Object& connectionJson);

                       
} // namespace connections
} // namespace modules
} // namesapce session
} // namespace rstudio

#endif // SESSION_CONNECTIONS_CONNECTION_HPP
