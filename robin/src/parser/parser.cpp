//
// Created by icelake on 24-5-16.
//

#include "parser.h"

namespace parser {

    Map<Pair<State, Symbol>, Action> Parser::slrTable = {
            {{0,  Symbol::minus},        {Type::Shift,  5}},
            {{0,  Symbol::plus},         {Type::Error,  0}},
            {{0,  Symbol::div},          {Type::Error,  0}},
            {{0,  Symbol::star},         {Type::Error,  0}},
            {{0,  Symbol::mod},          {Type::Error,  0}},
            {{0,  Symbol::left_paren},   {Type::Shift,  8}},
            {{0,  Symbol::right_paren},  {Type::Reduce, 2}},
            {{0,  Symbol::int_},         {Type::Shift,  9}},
            {{0,  Symbol::real_},        {Type::Shift,  10}},
            {{0,  Symbol::dollar},       {Type::Error,  0}},
            {{0,  Symbol::Expr},         {Type::Error,  0}},
            {{0,  Symbol::expression},   {Type::Goto,   1}},
            {{0,  Symbol::term},         {Type::Goto,   2}},
            {{0,  Symbol::term_prime},   {Type::Error,  0}},
            {{0,  Symbol::factor},       {Type::Goto,   3}},
            {{0,  Symbol::factor_prime}, {Type::Error,  0}},
            {{0,  Symbol::unary},        {Type::Goto,   4}},
            {{0,  Symbol::primary},      {Type::Goto,   6}},
            {{0,  Symbol::number},       {Type::Goto,   7}},

            {{1,  Symbol::minus},        {Type::Error,  0}},
            {{1,  Symbol::plus},         {Type::Error,  0}},
            {{1,  Symbol::div},          {Type::Error,  0}},
            {{1,  Symbol::star},         {Type::Error,  0}},
            {{1,  Symbol::mod},          {Type::Error,  0}},
            {{1,  Symbol::number},       {Type::Error,  0}},
            {{1,  Symbol::left_paren},   {Type::Error,  0}},
            {{1,  Symbol::right_paren},  {Type::Error,  0}},
            {{1,  Symbol::int_},         {Type::Error,  0}},
            {{1,  Symbol::real_},        {Type::Error,  0}},
            {{1,  Symbol::dollar},       {Type::Accept, 1}},
            {{1,  Symbol::Expr},         {Type::Error,  0}},
            {{1,  Symbol::expression},   {Type::Error,  0}},
            {{1,  Symbol::term},         {Type::Error,  0}},
            {{1,  Symbol::term_prime},   {Type::Error,  0}},
            {{1,  Symbol::factor},       {Type::Error,  0}},
            {{1,  Symbol::factor_prime}, {Type::Error,  0}},
            {{1,  Symbol::unary},        {Type::Error,  0}},
            {{1,  Symbol::primary},      {Type::Error,  0}},
            {{1,  Symbol::number},       {Type::Error,  0}},

            {{2,  Symbol::minus},        {Type::Error,  0}},
            {{2,  Symbol::plus},         {Type::Error,  0}},
            {{2,  Symbol::div},          {Type::Error,  0}},
            {{2,  Symbol::star},         {Type::Error,  0}},
            {{2,  Symbol::mod},          {Type::Error,  0}},
            {{2,  Symbol::left_paren},   {Type::Error,  0}},
            {{2,  Symbol::right_paren},  {Type::Reduce, 1}},
            {{2,  Symbol::int_},         {Type::Error,  0}},
            {{2,  Symbol::real_},        {Type::Error,  0}},
            {{2,  Symbol::dollar},       {Type::Reduce, 1}},
            {{2,  Symbol::Expr},         {Type::Error,  0}},
            {{2,  Symbol::expression},   {Type::Error,  0}},
            {{2,  Symbol::term},         {Type::Error,  0}},
            {{2,  Symbol::term_prime},   {Type::Error,  0}},
            {{2,  Symbol::factor},       {Type::Error,  0}},
            {{2,  Symbol::factor_prime}, {Type::Error,  0}},
            {{2,  Symbol::unary},        {Type::Error,  0}},
            {{2,  Symbol::primary},      {Type::Error,  0}},
            {{2,  Symbol::number},       {Type::Error,  0}},

            {{3,  Symbol::minus},        {Type::Shift,  12}},
            {{3,  Symbol::plus},         {Type::Shift,  13}},
            {{3,  Symbol::div},          {Type::Error,  0}},
            {{3,  Symbol::star},         {Type::Error,  0}},
            {{3,  Symbol::mod},          {Type::Error,  0}},
            {{3,  Symbol::left_paren},   {Type::Error,  0}},
            {{3,  Symbol::right_paren},  {Type::Reduce, 6}},
            {{3,  Symbol::int_},         {Type::Error,  0}},
            {{3,  Symbol::real_},        {Type::Error,  0}},
            {{3,  Symbol::dollar},       {Type::Reduce, 6}},
            {{3,  Symbol::Expr},         {Type::Error,  0}},
            {{3,  Symbol::expression},   {Type::Error,  0}},
            {{3,  Symbol::term},         {Type::Error,  0}},
            {{3,  Symbol::term_prime},   {Type::Goto,   11}},
            {{3,  Symbol::factor},       {Type::Error,  0}},
            {{3,  Symbol::factor_prime}, {Type::Error,  0}},
            {{3,  Symbol::unary},        {Type::Error,  0}},
            {{3,  Symbol::primary},      {Type::Error,  0}},
            {{3,  Symbol::number},       {Type::Error,  0}},

            {{4,  Symbol::minus},        {Type::Reduce, 11}},
            {{4,  Symbol::plus},         {Type::Reduce, 11}},
            {{4,  Symbol::div},          {Type::Shift,  15}},
            {{4,  Symbol::star},         {Type::Shift,  16}},
            {{4,  Symbol::mod},          {Type::Shift,  17}},
            {{4,  Symbol::left_paren},   {Type::Error,  0}},
            {{4,  Symbol::right_paren},  {Type::Reduce, 11}},
            {{4,  Symbol::int_},         {Type::Error,  0}},
            {{4,  Symbol::real_},        {Type::Error,  0}},
            {{4,  Symbol::dollar},       {Type::Reduce, 11}},
            {{4,  Symbol::Expr},         {Type::Error,  0}},
            {{4,  Symbol::expression},   {Type::Error,  0}},
            {{4,  Symbol::term},         {Type::Error,  0}},
            {{4,  Symbol::term_prime},   {Type::Error,  0}},
            {{4,  Symbol::factor},       {Type::Error,  0}},
            {{4,  Symbol::factor_prime}, {Type::Goto,   14}},
            {{4,  Symbol::unary},        {Type::Error,  0}},
            {{4,  Symbol::primary},      {Type::Error,  0}},
            {{4,  Symbol::number},       {Type::Error,  0}},

            {{5,  Symbol::minus},        {Type::Shift,  5}},
            {{5,  Symbol::plus},         {Type::Error,  0}},
            {{5,  Symbol::div},          {Type::Error,  0}},
            {{5,  Symbol::star},         {Type::Error,  0}},
            {{5,  Symbol::mod},          {Type::Error,  0}},
            {{5,  Symbol::left_paren},   {Type::Shift,  8}},
            {{5,  Symbol::right_paren},  {Type::Error,  0}},
            {{5,  Symbol::int_},         {Type::Shift,  9}},
            {{5,  Symbol::real_},        {Type::Shift,  10}},
            {{5,  Symbol::dollar},       {Type::Error,  0}},
            {{5,  Symbol::Expr},         {Type::Error,  0}},
            {{5,  Symbol::expression},   {Type::Error,  0}},
            {{5,  Symbol::term},         {Type::Error,  0}},
            {{5,  Symbol::term_prime},   {Type::Error,  0}},
            {{5,  Symbol::factor},       {Type::Error,  0}},
            {{5,  Symbol::factor_prime}, {Type::Error,  0}},
            {{5,  Symbol::unary},        {Type::Goto,   18}},
            {{5,  Symbol::primary},      {Type::Goto,   6}},
            {{5,  Symbol::number},       {Type::Error,  7}},

            {{6,  Symbol::minus},        {Type::Reduce, 13}},
            {{6,  Symbol::plus},         {Type::Reduce, 13}},
            {{6,  Symbol::div},          {Type::Reduce, 13}},
            {{6,  Symbol::star},         {Type::Reduce, 13}},
            {{6,  Symbol::mod},          {Type::Reduce, 13}},
            {{6,  Symbol::left_paren},   {Type::Error,  0}},
            {{6,  Symbol::right_paren},  {Type::Reduce, 13}},
            {{6,  Symbol::int_},         {Type::Error,  0}},
            {{6,  Symbol::real_},        {Type::Error,  0}},
            {{6,  Symbol::dollar},       {Type::Reduce, 13}},
            {{6,  Symbol::Expr},         {Type::Error,  0}},
            {{6,  Symbol::expression},   {Type::Error,  0}},
            {{6,  Symbol::term},         {Type::Error,  0}},
            {{6,  Symbol::term_prime},   {Type::Error,  0}},
            {{6,  Symbol::factor},       {Type::Error,  0}},
            {{6,  Symbol::factor_prime}, {Type::Error,  0}},
            {{6,  Symbol::unary},        {Type::Error,  0}},
            {{6,  Symbol::primary},      {Type::Error,  0}},
            {{6,  Symbol::number},       {Type::Error,  0}},

            {{7,  Symbol::minus},        {Type::Reduce, 14}},
            {{7,  Symbol::plus},         {Type::Reduce, 14}},
            {{7,  Symbol::div},          {Type::Reduce, 14}},
            {{7,  Symbol::star},         {Type::Reduce, 14}},
            {{7,  Symbol::mod},          {Type::Reduce, 14}},
            {{7,  Symbol::left_paren},   {Type::Error,  0}},
            {{7,  Symbol::right_paren},  {Type::Reduce, 14}},
            {{7,  Symbol::int_},         {Type::Error,  0}},
            {{7,  Symbol::real_},        {Type::Error,  0}},
            {{7,  Symbol::dollar},       {Type::Reduce, 14}},
            {{7,  Symbol::Expr},         {Type::Error,  0}},
            {{7,  Symbol::expression},   {Type::Error,  0}},
            {{7,  Symbol::term},         {Type::Error,  0}},
            {{7,  Symbol::term_prime},   {Type::Error,  0}},
            {{7,  Symbol::factor},       {Type::Error,  0}},
            {{7,  Symbol::factor_prime}, {Type::Error,  0}},
            {{7,  Symbol::unary},        {Type::Error,  0}},
            {{7,  Symbol::primary},      {Type::Error,  0}},
            {{7,  Symbol::number},       {Type::Error,  0}},

            {{8,  Symbol::minus},        {Type::Shift,  5}},
            {{8,  Symbol::plus},         {Type::Error,  0}},
            {{8,  Symbol::div},          {Type::Error,  0}},
            {{8,  Symbol::star},         {Type::Error,  0}},
            {{8,  Symbol::mod},          {Type::Error,  0}},
            {{8,  Symbol::left_paren},   {Type::Shift,  8}},
            {{8,  Symbol::right_paren},  {Type::Reduce, 2}},
            {{8,  Symbol::int_},         {Type::Shift,  9}},
            {{8,  Symbol::real_},        {Type::Shift,  10}},
            {{8,  Symbol::dollar},       {Type::Reduce, 2}},
            {{8,  Symbol::Expr},         {Type::Error,  0}},
            {{8,  Symbol::expression},   {Type::Goto,   19}},
            {{8,  Symbol::term},         {Type::Goto,   2}},
            {{8,  Symbol::term_prime},   {Type::Error,  0}},
            {{8,  Symbol::factor},       {Type::Goto,   3}},
            {{8,  Symbol::factor_prime}, {Type::Error,  0}},
            {{8,  Symbol::unary},        {Type::Goto,   4}},
            {{8,  Symbol::primary},      {Type::Goto,   6}},
            {{8,  Symbol::number},       {Type::Goto,   7}},

            {{9,  Symbol::minus},        {Type::Reduce, 16}},
            {{9,  Symbol::plus},         {Type::Reduce, 16}},
            {{9,  Symbol::div},          {Type::Reduce, 16}},
            {{9,  Symbol::star},         {Type::Reduce, 16}},
            {{9,  Symbol::mod},          {Type::Reduce, 16}},
            {{9,  Symbol::left_paren},   {Type::Error,  0}},
            {{9,  Symbol::right_paren},  {Type::Reduce, 16}},
            {{9,  Symbol::int_},         {Type::Error,  0}},
            {{9,  Symbol::real_},        {Type::Error,  0}},
            {{9,  Symbol::dollar},       {Type::Reduce, 16}},
            {{9,  Symbol::Expr},         {Type::Error,  0}},
            {{9,  Symbol::expression},   {Type::Error,  0}},
            {{9,  Symbol::term},         {Type::Error,  0}},
            {{9,  Symbol::term_prime},   {Type::Error,  0}},
            {{9,  Symbol::factor},       {Type::Error,  0}},
            {{9,  Symbol::factor_prime}, {Type::Error,  0}},
            {{9,  Symbol::unary},        {Type::Error,  0}},
            {{9,  Symbol::primary},      {Type::Error,  0}},
            {{9,  Symbol::number},       {Type::Error,  0}},

            {{10, Symbol::minus},        {Type::Reduce, 17}},
            {{10, Symbol::plus},         {Type::Reduce, 17}},
            {{10, Symbol::div},          {Type::Reduce, 17}},
            {{10, Symbol::star},         {Type::Reduce, 17}},
            {{10, Symbol::mod},          {Type::Reduce, 17}},
            {{10, Symbol::left_paren},   {Type::Error,  0}},
            {{10, Symbol::right_paren},  {Type::Reduce, 17}},
            {{10, Symbol::int_},         {Type::Error,  0}},
            {{10, Symbol::real_},        {Type::Error,  0}},
            {{10, Symbol::dollar},       {Type::Reduce, 17}},
            {{10, Symbol::Expr},         {Type::Error,  0}},
            {{10, Symbol::expression},   {Type::Error,  0}},
            {{10, Symbol::term},         {Type::Error,  0}},
            {{10, Symbol::term_prime},   {Type::Error,  0}},
            {{10, Symbol::factor},       {Type::Error,  0}},
            {{10, Symbol::factor_prime}, {Type::Error,  0}},
            {{10, Symbol::unary},        {Type::Error,  0}},
            {{10, Symbol::primary},      {Type::Error,  0}},
            {{10, Symbol::number},       {Type::Error,  0}},

            {{11, Symbol::minus},        {Type::Error,  0}},
            {{11, Symbol::plus},         {Type::Error,  0}},
            {{11, Symbol::div},          {Type::Error,  0}},
            {{11, Symbol::star},         {Type::Error,  0}},
            {{11, Symbol::mod},          {Type::Error,  0}},
            {{11, Symbol::left_paren},   {Type::Error,  0}},
            {{11, Symbol::right_paren},  {Type::Reduce, 3}},
            {{11, Symbol::int_},         {Type::Error,  0}},
            {{11, Symbol::real_},        {Type::Error,  0}},
            {{11, Symbol::dollar},       {Type::Reduce, 3}},
            {{11, Symbol::Expr},         {Type::Error,  0}},
            {{11, Symbol::expression},   {Type::Error,  0}},
            {{11, Symbol::term},         {Type::Error,  0}},
            {{11, Symbol::term_prime},   {Type::Error,  0}},
            {{11, Symbol::factor},       {Type::Error,  0}},
            {{11, Symbol::factor_prime}, {Type::Error,  0}},
            {{11, Symbol::unary},        {Type::Error,  0}},
            {{11, Symbol::primary},      {Type::Error,  0}},
            {{11, Symbol::number},       {Type::Error,  0}},

            {{12, Symbol::minus},        {Type::Shift,  5}},
            {{12, Symbol::plus},         {Type::Error,  0}},
            {{12, Symbol::div},          {Type::Error,  0}},
            {{12, Symbol::star},         {Type::Error,  0}},
            {{12, Symbol::mod},          {Type::Error,  0}},
            {{12, Symbol::left_paren},   {Type::Shift,  8}},
            {{12, Symbol::right_paren},  {Type::Error,  0}},
            {{12, Symbol::int_},         {Type::Shift,  9}},
            {{12, Symbol::real_},        {Type::Shift,  10}},
            {{12, Symbol::dollar},       {Type::Error,  0}},
            {{12, Symbol::Expr},         {Type::Error,  0}},
            {{12, Symbol::expression},   {Type::Error,  0}},
            {{12, Symbol::term},         {Type::Error,  0}},
            {{12, Symbol::term_prime},   {Type::Error,  0}},
            {{12, Symbol::factor},       {Type::Goto,   20}},
            {{12, Symbol::factor_prime}, {Type::Error,  0}},
            {{12, Symbol::unary},        {Type::Goto,   4}},
            {{12, Symbol::primary},      {Type::Goto,   6}},
            {{12, Symbol::number},       {Type::Goto,   7}},

            {{13, Symbol::minus},        {Type::Shift,  5}},
            {{13, Symbol::plus},         {Type::Error,  0}},
            {{13, Symbol::div},          {Type::Error,  0}},
            {{13, Symbol::star},         {Type::Error,  0}},
            {{13, Symbol::mod},          {Type::Error,  0}},
            {{13, Symbol::left_paren},   {Type::Shift,  8}},
            {{13, Symbol::right_paren},  {Type::Error,  0}},
            {{13, Symbol::int_},         {Type::Shift,  9}},
            {{13, Symbol::real_},        {Type::Shift,  10}},
            {{13, Symbol::dollar},       {Type::Error,  0}},
            {{13, Symbol::Expr},         {Type::Error,  0}},
            {{13, Symbol::expression},   {Type::Error,  0}},
            {{13, Symbol::term},         {Type::Error,  0}},
            {{13, Symbol::term_prime},   {Type::Error,  0}},
            {{13, Symbol::factor},       {Type::Goto,   21}},
            {{13, Symbol::factor_prime}, {Type::Error,  0}},
            {{13, Symbol::unary},        {Type::Goto,   4}},
            {{13, Symbol::primary},      {Type::Goto,   6}},
            {{13, Symbol::number},       {Type::Goto,   7}},

            {{14, Symbol::minus},        {Type::Reduce, 7}},
            {{14, Symbol::plus},         {Type::Reduce, 7}},
            {{14, Symbol::div},          {Type::Error,  0}},
            {{14, Symbol::star},         {Type::Error,  0}},
            {{14, Symbol::mod},          {Type::Error,  0}},
            {{14, Symbol::left_paren},   {Type::Error,  0}},
            {{14, Symbol::right_paren},  {Type::Reduce, 7}},
            {{14, Symbol::int_},         {Type::Error,  0}},
            {{14, Symbol::real_},        {Type::Error,  0}},
            {{14, Symbol::dollar},       {Type::Reduce, 7}},
            {{14, Symbol::Expr},         {Type::Error,  0}},
            {{14, Symbol::expression},   {Type::Error,  0}},
            {{14, Symbol::term},         {Type::Error,  0}},
            {{14, Symbol::term_prime},   {Type::Error,  0}},
            {{14, Symbol::factor},       {Type::Error,  0}},
            {{14, Symbol::factor_prime}, {Type::Error,  0}},
            {{14, Symbol::unary},        {Type::Error,  0}},
            {{14, Symbol::primary},      {Type::Error,  0}},
            {{14, Symbol::number},       {Type::Error,  0}},

            {{15, Symbol::minus},        {Type::Shift,  5}},
            {{15, Symbol::plus},         {Type::Error,  0}},
            {{15, Symbol::div},          {Type::Error,  0}},
            {{15, Symbol::star},         {Type::Error,  0}},
            {{15, Symbol::mod},          {Type::Error,  0}},
            {{15, Symbol::left_paren},   {Type::Shift,  8}},
            {{15, Symbol::right_paren},  {Type::Error,  0}},
            {{15, Symbol::int_},         {Type::Shift,  9}},
            {{15, Symbol::real_},        {Type::Shift,  10}},
            {{15, Symbol::dollar},       {Type::Error,  0}},
            {{15, Symbol::Expr},         {Type::Error,  0}},
            {{15, Symbol::expression},   {Type::Error,  0}},
            {{15, Symbol::term},         {Type::Error,  0}},
            {{15, Symbol::term_prime},   {Type::Error,  0}},
            {{15, Symbol::factor},       {Type::Error,  0}},
            {{15, Symbol::factor_prime}, {Type::Error,  0}},
            {{15, Symbol::unary},        {Type::Goto,   22}},
            {{15, Symbol::primary},      {Type::Goto,   6}},
            {{15, Symbol::number},       {Type::Goto,   7}},

            {{16, Symbol::minus},        {Type::Shift,  5}},
            {{16, Symbol::plus},         {Type::Error,  0}},
            {{16, Symbol::div},          {Type::Error,  0}},
            {{16, Symbol::star},         {Type::Error,  0}},
            {{16, Symbol::mod},          {Type::Error,  0}},
            {{16, Symbol::left_paren},   {Type::Shift,  8}},
            {{16, Symbol::right_paren},  {Type::Error,  0}},
            {{16, Symbol::int_},         {Type::Shift,  9}},
            {{16, Symbol::real_},        {Type::Shift,  10}},
            {{16, Symbol::dollar},       {Type::Error,  0}},
            {{16, Symbol::Expr},         {Type::Error,  0}},
            {{16, Symbol::expression},   {Type::Error,  0}},
            {{16, Symbol::term},         {Type::Error,  0}},
            {{16, Symbol::term_prime},   {Type::Error,  0}},
            {{16, Symbol::factor},       {Type::Error,  0}},
            {{16, Symbol::factor_prime}, {Type::Error,  0}},
            {{16, Symbol::unary},        {Type::Goto,   23}},
            {{16, Symbol::primary},      {Type::Goto,   6}},
            {{16, Symbol::number},       {Type::Goto,   7}},

            {{17, Symbol::minus},        {Type::Shift,  5}},
            {{17, Symbol::plus},         {Type::Error,  0}},
            {{17, Symbol::div},          {Type::Error,  0}},
            {{17, Symbol::star},         {Type::Error,  0}},
            {{17, Symbol::mod},          {Type::Error,  0}},
            {{17, Symbol::left_paren},   {Type::Shift,  8}},
            {{17, Symbol::right_paren},  {Type::Error,  0}},
            {{17, Symbol::int_},         {Type::Shift,  9}},
            {{17, Symbol::real_},        {Type::Shift,  10}},
            {{17, Symbol::dollar},       {Type::Error,  0}},
            {{17, Symbol::Expr},         {Type::Error,  0}},
            {{17, Symbol::expression},   {Type::Error,  0}},
            {{17, Symbol::term},         {Type::Error,  0}},
            {{17, Symbol::term_prime},   {Type::Error,  0}},
            {{17, Symbol::factor},       {Type::Error,  0}},
            {{17, Symbol::factor_prime}, {Type::Error,  0}},
            {{17, Symbol::unary},        {Type::Goto,   24}},
            {{17, Symbol::primary},      {Type::Goto,   6}},
            {{17, Symbol::number},       {Type::Goto,   7}},

            {{18, Symbol::minus},        {Type::Reduce, 12}},
            {{18, Symbol::plus},         {Type::Reduce, 12}},
            {{18, Symbol::div},          {Type::Reduce, 12}},
            {{18, Symbol::star},         {Type::Reduce, 12}},
            {{18, Symbol::mod},          {Type::Reduce, 12}},
            {{18, Symbol::left_paren},   {Type::Error,  0}},
            {{18, Symbol::right_paren},  {Type::Reduce, 12}},
            {{18, Symbol::int_},         {Type::Error,  0}},
            {{18, Symbol::real_},        {Type::Error,  0}},
            {{18, Symbol::dollar},       {Type::Reduce, 12}},
            {{18, Symbol::Expr},         {Type::Error,  0}},
            {{18, Symbol::expression},   {Type::Error,  0}},
            {{18, Symbol::term},         {Type::Error,  0}},
            {{18, Symbol::term_prime},   {Type::Error,  0}},
            {{18, Symbol::factor},       {Type::Error,  0}},
            {{18, Symbol::factor_prime}, {Type::Error,  0}},
            {{18, Symbol::unary},        {Type::Error,  0}},
            {{18, Symbol::primary},      {Type::Error,  0}},
            {{18, Symbol::number},       {Type::Error,  0}},

            {{19, Symbol::minus},        {Type::Error,  0}},
            {{19, Symbol::plus},         {Type::Error,  0}},
            {{19, Symbol::div},          {Type::Error,  0}},
            {{19, Symbol::star},         {Type::Error,  0}},
            {{19, Symbol::mod},          {Type::Error,  0}},
            {{19, Symbol::left_paren},   {Type::Error,  0}},
            {{19, Symbol::right_paren},  {Type::Shift,  25}},
            {{19, Symbol::int_},         {Type::Error,  0}},
            {{19, Symbol::real_},        {Type::Error,  0}},
            {{19, Symbol::dollar},       {Type::Error,  0}},
            {{19, Symbol::Expr},         {Type::Error,  0}},
            {{19, Symbol::expression},   {Type::Error,  0}},
            {{19, Symbol::term},         {Type::Error,  0}},
            {{19, Symbol::term_prime},   {Type::Error,  0}},
            {{19, Symbol::factor},       {Type::Error,  0}},
            {{19, Symbol::factor_prime}, {Type::Error,  0}},
            {{19, Symbol::unary},        {Type::Error,  0}},
            {{19, Symbol::primary},      {Type::Error,  0}},
            {{19, Symbol::number},       {Type::Error,  0}},

            {{20, Symbol::minus},        {Type::Shift,  12}},
            {{20, Symbol::plus},         {Type::Shift,  13}},
            {{20, Symbol::div},          {Type::Error,  0}},
            {{20, Symbol::star},         {Type::Error,  0}},
            {{20, Symbol::mod},          {Type::Error,  0}},
            {{20, Symbol::left_paren},   {Type::Error,  0}},
            {{20, Symbol::right_paren},  {Type::Reduce, 6}},
            {{20, Symbol::int_},         {Type::Error,  0}},
            {{20, Symbol::real_},        {Type::Error,  0}},
            {{20, Symbol::dollar},       {Type::Reduce, 6}},
            {{20, Symbol::Expr},         {Type::Error,  0}},
            {{20, Symbol::expression},   {Type::Error,  0}},
            {{20, Symbol::term},         {Type::Error,  0}},
            {{20, Symbol::term_prime},   {Type::Goto,   26}},
            {{20, Symbol::factor},       {Type::Error,  0}},
            {{20, Symbol::factor_prime}, {Type::Error,  0}},
            {{20, Symbol::unary},        {Type::Error,  0}},
            {{20, Symbol::primary},      {Type::Error,  0}},
            {{20, Symbol::number},       {Type::Error,  0}},

            {{21, Symbol::minus},        {Type::Shift,  12}},
            {{21, Symbol::plus},         {Type::Shift,  13}},
            {{21, Symbol::div},          {Type::Error,  0}},
            {{21, Symbol::star},         {Type::Error,  0}},
            {{21, Symbol::mod},          {Type::Error,  0}},
            {{21, Symbol::left_paren},   {Type::Error,  0}},
            {{21, Symbol::right_paren},  {Type::Reduce, 6}},
            {{21, Symbol::int_},         {Type::Error,  0}},
            {{21, Symbol::real_},        {Type::Error,  0}},
            {{21, Symbol::dollar},       {Type::Reduce, 6}},
            {{21, Symbol::Expr},         {Type::Error,  0}},
            {{21, Symbol::expression},   {Type::Error,  0}},
            {{21, Symbol::term},         {Type::Error,  0}},
            {{21, Symbol::term_prime},   {Type::Goto,   27}},
            {{21, Symbol::factor},       {Type::Error,  0}},
            {{21, Symbol::factor_prime}, {Type::Error,  0}},
            {{21, Symbol::unary},        {Type::Error,  0}},
            {{21, Symbol::primary},      {Type::Error,  0}},
            {{21, Symbol::number},       {Type::Error,  0}},

            {{22, Symbol::minus},        {Type::Reduce, 11}},
            {{22, Symbol::plus},         {Type::Reduce, 11}},
            {{22, Symbol::div},          {Type::Shift,  15}},
            {{22, Symbol::star},         {Type::Shift,  16}},
            {{22, Symbol::mod},          {Type::Shift,  17}},
            {{22, Symbol::left_paren},   {Type::Error,  0}},
            {{22, Symbol::right_paren},  {Type::Reduce, 11}},
            {{22, Symbol::int_},         {Type::Error,  0}},
            {{22, Symbol::real_},        {Type::Error,  0}},
            {{22, Symbol::dollar},       {Type::Reduce, 11}},
            {{22, Symbol::Expr},         {Type::Error,  0}},
            {{22, Symbol::expression},   {Type::Error,  0}},
            {{22, Symbol::term},         {Type::Error,  0}},
            {{22, Symbol::term_prime},   {Type::Error,  0}},
            {{22, Symbol::factor},       {Type::Error,  0}},
            {{22, Symbol::factor_prime}, {Type::Goto,   28}},
            {{22, Symbol::unary},        {Type::Error,  0}},
            {{22, Symbol::primary},      {Type::Error,  0}},
            {{22, Symbol::number},       {Type::Error,  0}},

            {{23, Symbol::minus},        {Type::Reduce, 11}},
            {{23, Symbol::plus},         {Type::Reduce, 11}},
            {{23, Symbol::div},          {Type::Shift,  15}},
            {{23, Symbol::star},         {Type::Shift,  16}},
            {{23, Symbol::mod},          {Type::Shift,  17}},
            {{23, Symbol::left_paren},   {Type::Error,  0}},
            {{23, Symbol::right_paren},  {Type::Reduce, 11}},
            {{23, Symbol::int_},         {Type::Error,  0}},
            {{23, Symbol::real_},        {Type::Error,  0}},
            {{23, Symbol::dollar},       {Type::Reduce, 11}},
            {{23, Symbol::Expr},         {Type::Error,  0}},
            {{23, Symbol::expression},   {Type::Error,  0}},
            {{23, Symbol::term},         {Type::Error,  0}},
            {{23, Symbol::term_prime},   {Type::Error,  0}},
            {{23, Symbol::factor},       {Type::Error,  0}},
            {{23, Symbol::factor_prime}, {Type::Goto,   29}},
            {{23, Symbol::unary},        {Type::Error,  0}},
            {{23, Symbol::primary},      {Type::Error,  0}},
            {{23, Symbol::number},       {Type::Error,  0}},

            {{24, Symbol::minus},        {Type::Reduce, 11}},
            {{24, Symbol::plus},         {Type::Reduce, 11}},
            {{24, Symbol::div},          {Type::Shift,  15}},
            {{24, Symbol::star},         {Type::Shift,  16}},
            {{24, Symbol::mod},          {Type::Shift,  17}},
            {{24, Symbol::left_paren},   {Type::Error,  0}},
            {{24, Symbol::right_paren},  {Type::Reduce, 11}},
            {{24, Symbol::int_},         {Type::Error,  0}},
            {{24, Symbol::real_},        {Type::Error,  0}},
            {{24, Symbol::dollar},       {Type::Reduce, 11}},
            {{24, Symbol::Expr},         {Type::Error,  0}},
            {{24, Symbol::expression},   {Type::Error,  0}},
            {{24, Symbol::term},         {Type::Error,  0}},
            {{24, Symbol::term_prime},   {Type::Error,  0}},
            {{24, Symbol::factor},       {Type::Error,  0}},
            {{24, Symbol::factor_prime}, {Type::Goto,   30}},
            {{24, Symbol::unary},        {Type::Error,  0}},
            {{24, Symbol::primary},      {Type::Error,  0}},
            {{24, Symbol::number},       {Type::Error,  0}},

            {{25, Symbol::minus},        {Type::Reduce, 15}},
            {{25, Symbol::plus},         {Type::Reduce, 15}},
            {{25, Symbol::div},          {Type::Reduce, 15}},
            {{25, Symbol::star},         {Type::Reduce, 15}},
            {{25, Symbol::mod},          {Type::Reduce, 15}},
            {{25, Symbol::left_paren},   {Type::Error,  0}},
            {{25, Symbol::right_paren},  {Type::Reduce, 15}},
            {{25, Symbol::int_},         {Type::Error,  0}},
            {{25, Symbol::real_},        {Type::Error,  0}},
            {{25, Symbol::dollar},       {Type::Reduce, 15}},
            {{25, Symbol::Expr},         {Type::Error,  0}},
            {{25, Symbol::expression},   {Type::Error,  0}},
            {{25, Symbol::term},         {Type::Error,  0}},
            {{25, Symbol::term_prime},   {Type::Error,  0}},
            {{25, Symbol::factor},       {Type::Error,  0}},
            {{25, Symbol::factor_prime}, {Type::Error,  0}},
            {{25, Symbol::unary},        {Type::Error,  0}},
            {{25, Symbol::primary},      {Type::Error,  0}},
            {{25, Symbol::number},       {Type::Error,  0}},

            {{26, Symbol::minus},        {Type::Error,  0}},
            {{26, Symbol::plus},         {Type::Error,  0}},
            {{26, Symbol::div},          {Type::Error,  0}},
            {{26, Symbol::star},         {Type::Error,  0}},
            {{26, Symbol::mod},          {Type::Error,  0}},
            {{26, Symbol::left_paren},   {Type::Error,  0}},
            {{26, Symbol::right_paren},  {Type::Reduce, 4}},
            {{26, Symbol::int_},         {Type::Error,  0}},
            {{26, Symbol::real_},        {Type::Error,  0}},
            {{26, Symbol::dollar},       {Type::Reduce, 4}},
            {{26, Symbol::Expr},         {Type::Error,  0}},
            {{26, Symbol::expression},   {Type::Error,  0}},
            {{26, Symbol::term},         {Type::Error,  0}},
            {{26, Symbol::term_prime},   {Type::Error,  0}},
            {{26, Symbol::factor},       {Type::Error,  0}},
            {{26, Symbol::factor_prime}, {Type::Error,  0}},
            {{26, Symbol::unary},        {Type::Error,  0}},
            {{26, Symbol::primary},      {Type::Error,  0}},
            {{26, Symbol::number},       {Type::Error,  0}},

            {{27, Symbol::minus},        {Type::Error,  0}},
            {{27, Symbol::plus},         {Type::Error,  0}},
            {{27, Symbol::div},          {Type::Error,  0}},
            {{27, Symbol::star},         {Type::Error,  0}},
            {{27, Symbol::mod},          {Type::Error,  0}},
            {{27, Symbol::left_paren},   {Type::Error,  0}},
            {{27, Symbol::right_paren},  {Type::Reduce, 5}},
            {{27, Symbol::int_},         {Type::Error,  0}},
            {{27, Symbol::real_},        {Type::Error,  0}},
            {{27, Symbol::dollar},       {Type::Reduce, 5}},
            {{27, Symbol::Expr},         {Type::Error,  0}},
            {{27, Symbol::expression},   {Type::Error,  0}},
            {{27, Symbol::term},         {Type::Error,  0}},
            {{27, Symbol::term_prime},   {Type::Error,  0}},
            {{27, Symbol::factor},       {Type::Error,  0}},
            {{27, Symbol::factor_prime}, {Type::Error,  0}},
            {{27, Symbol::unary},        {Type::Error,  0}},
            {{27, Symbol::primary},      {Type::Error,  0}},
            {{27, Symbol::number},       {Type::Error,  0}},

            {{28, Symbol::minus},        {Type::Reduce, 8}},
            {{28, Symbol::plus},         {Type::Reduce, 8}},
            {{28, Symbol::div},          {Type::Error,  0}},
            {{28, Symbol::star},         {Type::Error,  0}},
            {{28, Symbol::mod},          {Type::Error,  0}},
            {{28, Symbol::left_paren},   {Type::Error,  0}},
            {{28, Symbol::right_paren},  {Type::Reduce, 8}},
            {{28, Symbol::int_},         {Type::Error,  0}},
            {{28, Symbol::real_},        {Type::Error,  0}},
            {{28, Symbol::dollar},       {Type::Reduce, 8}},
            {{28, Symbol::Expr},         {Type::Error,  0}},
            {{28, Symbol::expression},   {Type::Error,  0}},
            {{28, Symbol::term},         {Type::Error,  0}},
            {{28, Symbol::term_prime},   {Type::Error,  0}},
            {{28, Symbol::factor},       {Type::Error,  0}},
            {{28, Symbol::factor_prime}, {Type::Error,  0}},
            {{28, Symbol::unary},        {Type::Error,  0}},
            {{28, Symbol::primary},      {Type::Error,  0}},
            {{28, Symbol::number},       {Type::Error,  0}},

            {{29, Symbol::minus},        {Type::Reduce, 9}},
            {{29, Symbol::plus},         {Type::Reduce, 9}},
            {{29, Symbol::div},          {Type::Error,  0}},
            {{29, Symbol::star},         {Type::Error,  0}},
            {{29, Symbol::mod},          {Type::Error,  0}},
            {{29, Symbol::left_paren},   {Type::Error,  0}},
            {{29, Symbol::right_paren},  {Type::Reduce, 9}},
            {{29, Symbol::int_},         {Type::Error,  0}},
            {{29, Symbol::real_},        {Type::Error,  0}},
            {{29, Symbol::dollar},       {Type::Reduce, 9}},
            {{29, Symbol::Expr},         {Type::Error,  0}},
            {{29, Symbol::expression},   {Type::Error,  0}},
            {{29, Symbol::term},         {Type::Error,  0}},
            {{29, Symbol::term_prime},   {Type::Error,  0}},
            {{29, Symbol::factor},       {Type::Error,  0}},
            {{29, Symbol::factor_prime}, {Type::Error,  0}},
            {{29, Symbol::unary},        {Type::Error,  0}},
            {{29, Symbol::primary},      {Type::Error,  0}},
            {{29, Symbol::number},       {Type::Error,  0}},

            {{30, Symbol::minus},        {Type::Reduce, 10}},
            {{30, Symbol::plus},         {Type::Reduce, 10}},
            {{30, Symbol::div},          {Type::Error,  0}},
            {{30, Symbol::star},         {Type::Error,  0}},
            {{30, Symbol::mod},          {Type::Error,  0}},
            {{30, Symbol::left_paren},   {Type::Error,  0}},
            {{30, Symbol::right_paren},  {Type::Reduce, 10}},
            {{30, Symbol::int_},         {Type::Error,  0}},
            {{30, Symbol::real_},        {Type::Error,  0}},
            {{30, Symbol::dollar},       {Type::Reduce, 10}},
            {{30, Symbol::Expr},         {Type::Error,  0}},
            {{30, Symbol::expression},   {Type::Error,  0}},
            {{30, Symbol::term},         {Type::Error,  0}},
            {{30, Symbol::term_prime},   {Type::Error,  0}},
            {{30, Symbol::factor},       {Type::Error,  0}},
            {{30, Symbol::factor_prime}, {Type::Error,  0}},
            {{30, Symbol::unary},        {Type::Error,  0}},
            {{30, Symbol::primary},      {Type::Error,  0}},
            {{30, Symbol::number},       {Type::Error,  0}},
    };


    Parser::Parser(List<token::Token> tokens) : tokens(std::move(tokens)) {}

    List<SharedPtr<production::Production>> Parser::parserAst() {
        while (true) {
            if (isAtTokenListEnd()) break;
            auto token = advance();

        }
        return productions;
    }

    bool Parser::isAtTokenListEnd() {
        return currentToken >= tokens.size();
    }

    bool Parser::isAtProductionListEnd() {
        return currentProduction >= productions.size();
    }

    token::Token Parser::advance() {
        currentToken++;
        return tokens[currentToken - 1];
    }

}
