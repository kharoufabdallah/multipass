/*
 * Copyright (C) 2017-2020 Canonical, Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "client.h"

#include <multipass/cli/client_common.h>
#include <multipass/console.h>
#include <multipass/constants.h>
#include <multipass/top_catch_all.h>

#include <QCoreApplication>

namespace mp = multipass;

namespace
{
int main_impl(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(mp::client_name);

    auto term = mp::Terminal::make_terminal();

    mp::ClientConfig config{mp::client::get_server_address(), mp::RpcConnectionType::ssl,
                            mp::client::get_cert_provider(), term.get()};
    mp::Client client{config};

    return client.run(QCoreApplication::arguments());
}
} // namespace

int main(int argc, char* argv[])
{
    return mp::top_catch_all("client", main_impl, argc, argv);
}
