/*
    Copyright (c) 2016 Sven Turowski <sventurowski@gmx.de>
    
    Created on 20.10.16

    This file is part of cppsql, a C++ collection.

    cppsql is free software; you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    As a special exception, the Contributors give you permission to link
    this library with independent modules to produce an executable,
    regardless of the license terms of these independent modules, and to
    copy and distribute the resulting executable under terms of your choice,
    provided that you also meet, for each linked independent module, the
    terms and conditions of the license of that module. An independent
    module is a module which is not derived from or based on this library.
    If you modify this library, you must extend this exception to your
    version of the library.

    cppsql is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
    License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <map>
#include <iostream>
#include <memory>
#include <defines.h>
#include <where.h>

using namespace cppsql;

int main(int argc, char* argv[])
{
    Query statement;
    statement.select("ORDER_ID", "O").select("USER_ID", "O")
            .from("ORDER", "O")
            .and_where("ORDER_ID", "12345", Comparison::EQUALS);
    std::cout << statement.get_select_statement() << std::endl;





    //AND (DATE_LAST IS NULL OR DATE_LAST = 0 OR DATE_LAST >= 20161107)
    Where test("DATE_LAST", "20161107", Comparison::GREATER_EQUALS_THAN, Operator::OR);
    Where test1("DATE_LAST", "0", test, Comparison::EQUALS, Operator::OR);
    Where test2("DATE_LAST", "", test, Comparison::IS_NULL, Operator::AND);
    std::cout << test2.to_string() << std::endl;

    //AND (ORDER_ID IN (SELECT ORDER_ID FROM SEPA_STANDIN_ODERS))
    Query query;
    query.select("ORDER_ID").from("SEPA_STANDIN_ODERS");
    Where test3("ORDER_ID", query, Comparison::IN, Operator::AND);
    std::cout << test3.to_string() << std::endl;

    //AND (DATE_END IS NULL AND (DATE_BEGIN IS NOT NULL OR TYPE = "NO_END"))
    Where test4("TYPE", "'NO_END'", Comparison::EQUALS, Operator::OR);
    Where test5("DATE_BEGIN", "", test4, Comparison::IS_NOT_NULL, Operator::AND);
    Where test6("DATE_END", "", test5, Comparison::IS_NULL, Operator::AND);
    std::cout << test6.to_string() << std::endl;


}
