<?xml-stylesheet type="text/xsl" href="analysis.xsl"?>
<test_results>
<info>
<name>autotester</name><parsing_time_taken>67.000000</parsing_time_taken>
</info>
<queries>
<query>
<id ReturnTuple="1" CondNum="1" RelNum="0" comment="Zero Clause, stmt">1</id><querystr><![CDATA[stmt s; Select s]]></querystr>
<stuans>1,11,2,12,18,4,16,13,3,5,7,8,10,14,15,17,19,6,9</stuans>
<correct>1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19</correct>
<time_taken>14.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" CondNum="1" RelNum="0" comment="Zero Clause, read">2</id><querystr><![CDATA[read r; Select r]]></querystr>
<stuans>1,11,2</stuans>
<correct>1,2,11</correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" CondNum="1" RelNum="0" comment="Zero Clause, print">3</id><querystr><![CDATA[print pn; Select pn]]></querystr>
<stuans>12,18,4</stuans>
<correct>4,12,18</correct>
<time_taken>7.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" CondNum="1" RelNum="0" comment="Zero Clause, while">4</id><querystr><![CDATA[while w; Select w]]></querystr>
<stuans>16</stuans>
<correct>16</correct>
<time_taken>6.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" CondNum="1" RelNum="0" comment="Zero Clause, if">5</id><querystr><![CDATA[if i; Select i]]></querystr>
<stuans>13,3,5,7,8</stuans>
<correct>3,5,7,8,13</correct>
<time_taken>6.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" CondNum="1" RelNum="0" comment="Zero Clause, assign">6</id><querystr><![CDATA[assign a; Select a]]></querystr>
<stuans>10,14,15,17,19,6,9</stuans>
<correct>6,9,10,14,15,17,19</correct>
<time_taken>6.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" CondNum="1" RelNum="0" comment="Zero Clause, variable">7</id><querystr><![CDATA[variable v; Select v]]></querystr>
<stuans>a,b,c,var1,x,y,z</stuans>
<correct>x,y,a,b,c,z,var1</correct>
<time_taken>7.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" CondNum="1" RelNum="0" comment="Zero Clause, constant">8</id><querystr><![CDATA[constant c; Select c]]></querystr>
<stuans>1,10,101,2,5,500</stuans>
<correct>1,2,101,500,5,10</correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Follows="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, stmt, Follows, If as the first stmt">9</id><querystr><![CDATA[stmt s; Select s such that Follows(3, s)]]></querystr>
<stuans>18</stuans>
<correct>18</correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Follows="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, stmt, Follows, Nested If as the first stmt">10</id><querystr><![CDATA[stmt s; Select s such that Follows(5, s)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Followsstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, stmt, Follows*, Ifs after print">11</id><querystr><![CDATA[stmt s; Select s such that Follows*(4, s)]]></querystr>
<stuans>5</stuans>
<correct>5</correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, if, Parent, If">12</id><querystr><![CDATA[if ifs; Select ifs such that Parent(3, ifs)]]></querystr>
<stuans>13,5</stuans>
<correct>5,13</correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, if, Parent, Nested If">13</id><querystr><![CDATA[if ifs; Select ifs such that Parent(5, ifs)]]></querystr>
<stuans>7</stuans>
<correct>7</correct>
<time_taken>7.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, if, Parent, Nested 2 level If">14</id><querystr><![CDATA[if ifs; Select ifs such that Parent(7, ifs)]]></querystr>
<stuans>8</stuans>
<correct>8</correct>
<time_taken>7.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parent="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, stmt, Parent, Nested 2 level If">15</id><querystr><![CDATA[stmt s; Select s such that Parent(7, s)]]></querystr>
<stuans>11,12,8</stuans>
<correct>8,11,12</correct>
<time_taken>6.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parentstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, if, Parent*, If">16</id><querystr><![CDATA[if ifs; Select ifs such that Parent*(3, ifs)]]></querystr>
<stuans>13,5,7,8</stuans>
<correct>5,7,8,13</correct>
<time_taken>8.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Parentstar="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, if, Parent*, Nested If">17</id><querystr><![CDATA[if ifs; Select ifs such that Parent*(5, ifs)]]></querystr>
<stuans>7,8</stuans>
<correct>7,8</correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Follows="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, assign, Follows, If">18</id><querystr><![CDATA[assign a1, a2; Select a1 such that Follows(a1, a2)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Uses="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, variable, Uses, Variables in If">19</id><querystr><![CDATA[variable v; Select v such that Uses(3, v)]]></querystr>
<stuans>a,b,c,x,y,z</stuans>
<correct>a,b,x,y,c,z</correct>
<time_taken>9.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Uses="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, variable, Uses, Variables in Nested If">20</id><querystr><![CDATA[variable v; Select v such that Uses(8, v)]]></querystr>
<stuans>x</stuans>
<correct>x</correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Uses="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, stmt, Uses, Inside Nested If">21</id><querystr><![CDATA[stmt s; Select s such that Uses(s, "z")]]></querystr>
<stuans>12,16,13,3,5,7,14,17</stuans>
<correct>3,5,7,12,13,14,16,17</correct>
<time_taken>8.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="1" Uses="1" SuchThat="1" CondNum="4" RelNum="1" comment="Single Clause, stmt, Uses, Wildcard for all Stmts">22</id><querystr><![CDATA[stmt s; Select s such that Uses(s, _)]]></querystr>
<stuans>12,18,4,16,13,3,5,7,8,10,14,17,19,6</stuans>
<correct>3,4,5,6,7,8,10,12,13,14,16,17,18,19</correct>
<time_taken>12.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Uses="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, assign, Uses, Wildcard for all Stmts">23</id><querystr><![CDATA[assign a; Select a such that Uses(a, "x")]]></querystr>
<stuans>10,14</stuans>
<correct>10,14</correct>
<time_taken>4.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Modifies="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, stmt, Modifies, Inside Nested If">24</id><querystr><![CDATA[stmt s; Select s such that Modifies(s, "x")]]></querystr>
<stuans>1,11,3,5,7,8,6,9</stuans>
<correct>1,3,5,6,7,8,9,11</correct>
<time_taken>7.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Modifies="1" UnnamedVar="1" SuchThat="1" CondNum="4" RelNum="1" comment="Single Clause, if, Modifies, Wildcard for all Stmts">25</id><querystr><![CDATA[if ifs; Select ifs such that Modifies(ifs, _)]]></querystr>
<stuans>13,3,5,7,8</stuans>
<correct>3,5,7,8,13</correct>
<time_taken>8.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Modifies="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, variable, Modifies, Nested If and Wildcard">26</id><querystr><![CDATA[variable v; Select v such that Modifies(7, v)]]></querystr>
<stuans>x,y</stuans>
<correct>x,y</correct>
<time_taken>5.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Follows="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, Follows, Return all stmts for a true clause">26</id><querystr><![CDATA[stmt s; Select s such that Follows(3, 18)]]></querystr>
<stuans>1,11,2,12,18,4,16,13,3,5,7,8,10,14,15,17,19,6,9</stuans>
<correct>1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19</correct>
<time_taken>10.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" Follows="1" SuchThat="1" CondNum="3" RelNum="1" comment="Single Clause, Follows, Return no stmt for a false clause">27</id><querystr><![CDATA[stmt s; Select s such that Follows(3, 4)]]></querystr>
<stuans></stuans>
<correct></correct>
<time_taken>7.000000</time_taken>
<passed/>
</query>
<query>
<id ReturnTuple="1" UnnamedVar="2" Pattern="1" CondNum="4" RelNum="0" comment="Single Clause, Pattern, LHS Wildcard, RHS Variable Matching">28</id><querystr><![CDATA[assign a; Select a pattern a(_, _"x"_)]]></querystr>
