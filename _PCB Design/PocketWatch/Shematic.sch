<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="8.6.3">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="2" unitdist="mm" unit="mm" style="lines" multiple="1" display="yes" altdistance="1" altunitdist="mm" altunit="mm"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="88" name="SimResults" color="9" fill="1" visible="yes" active="yes"/>
<layer number="89" name="SimProbes" color="9" fill="1" visible="yes" active="yes"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="Library">
<packages>
<package name="IV-9">
<text x="-5" y="1.73" size="1.8" layer="25" ratio="10">&gt;NAME</text>
<text x="-5" y="-2.73" size="1.8" layer="27" ratio="10">&gt;VALUE</text>
<pad name="1" x="0" y="-4.9944" drill="0.525"/>
<circle x="0" y="-4.9944" radius="1" width="0.3" layer="21"/>
<text x="0" y="-3.7458" size="1" layer="21">1</text>
<pad name="2" x="2.9357" y="-4.0406" drill="0.525"/>
<circle x="2.9357" y="-4.0406" radius="1" width="0.3" layer="21"/>
<text x="2.2017" y="-3.0304" size="1" layer="21">2</text>
<pad name="3" x="4.75" y="-1.5434" drill="0.525"/>
<circle x="4.75" y="-1.5434" radius="1" width="0.3" layer="21"/>
<text x="3.5625" y="-1.1575" size="1" layer="21">3</text>
<pad name="4" x="4.75" y="1.5434" drill="0.525"/>
<circle x="4.75" y="1.5434" radius="1" width="0.3" layer="21"/>
<text x="3.5625" y="1.1575" size="1" layer="21">4</text>
<pad name="5" x="2.9357" y="4.0406" drill="0.525"/>
<circle x="2.9357" y="4.0406" radius="1" width="0.3" layer="21"/>
<text x="2.2017" y="3.0304" size="1" layer="21">5</text>
<pad name="6" x="0" y="4.9944" drill="0.525"/>
<circle x="0" y="4.9944" radius="1" width="0.3" layer="21"/>
<text x="0" y="3.7458" size="1" layer="21">6</text>
<pad name="7" x="-2.9357" y="4.0406" drill="0.525"/>
<circle x="-2.9357" y="4.0406" radius="1" width="0.3" layer="21"/>
<text x="-2.2017" y="3.0304" size="1" layer="21">7</text>
<pad name="8" x="-4.75" y="1.5434" drill="0.525"/>
<circle x="-4.75" y="1.5434" radius="1" width="0.3" layer="21"/>
<text x="-3.5625" y="1.1575" size="1" layer="21">8</text>
<pad name="9" x="-4.75" y="-1.5434" drill="0.525"/>
<circle x="-4.75" y="-1.5434" radius="1" width="0.3" layer="21"/>
<text x="-3.5625" y="-1.1575" size="1" layer="21">9</text>
<circle x="0" y="0" radius="5.9944" width="0.3" layer="21"/>
<circle x="0" y="0" radius="5.4944" width="0.1" layer="39"/>
</package>
</packages>
<symbols>
<symbol name="IV-9">
<pin name="P$1" x="0" y="10.16" length="middle" rot="R270"/>
<pin name="P$2" x="-14" y="-10" length="middle" rot="R90"/>
<pin name="P$3" x="-10" y="-10" length="middle" rot="R90"/>
<pin name="P$4" x="-6" y="-10" length="middle" rot="R90"/>
<pin name="P$5" x="-2" y="-10" length="middle" rot="R90"/>
<pin name="P$6" x="2" y="-10" length="middle" rot="R90"/>
<pin name="P$7" x="6" y="-10" length="middle" rot="R90"/>
<pin name="P$8" x="10" y="-10" length="middle" rot="R90"/>
<pin name="P$9" x="14" y="-10" length="middle" rot="R90"/>
<wire x1="-16" y1="-6" x2="-16" y2="6" width="0.254" layer="94" curve="-180"/>
<wire x1="16" y1="6" x2="16" y2="-6" width="0.254" layer="94" curve="-180"/>
<wire x1="-16" y1="6" x2="16" y2="6" width="0.254" layer="94"/>
<wire x1="16" y1="-6" x2="-16" y2="-6" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="IV-9">
<gates>
<gate name="G$1" symbol="IV-9" x="0" y="0"/>
</gates>
<devices>
<device name="" package="IV-9">
<connects>
<connect gate="G$1" pin="P$1" pad="1"/>
<connect gate="G$1" pin="P$2" pad="2"/>
<connect gate="G$1" pin="P$3" pad="3"/>
<connect gate="G$1" pin="P$4" pad="4"/>
<connect gate="G$1" pin="P$5" pad="5"/>
<connect gate="G$1" pin="P$6" pad="6"/>
<connect gate="G$1" pin="P$7" pad="7"/>
<connect gate="G$1" pin="P$8" pad="8"/>
<connect gate="G$1" pin="P$9" pad="9"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="U$1" library="Library" deviceset="IV-9" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="U$1" gate="G$1" x="22" y="64"/>
</instances>
<busses>
</busses>
<nets>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
