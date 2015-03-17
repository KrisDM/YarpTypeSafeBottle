<?xml version="1.0" encoding="UTF-8"?>
<!-- Copyright: (C) 2013-2014 King's College London -->
<!-- Authors: Kris De Meyer -->
<!-- CopyPolicy: Released under the terms of the LGPLv2.1 or later -->
<xsl:transform version="1.0" xmlns:n1="http://darwin-project.eu/namespaces/TypeSafeBottle" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xs="http://www.w3.org/2001/XMLSchema" xmlns:fn="http://www.w3.org/2005/xpath-functions">
	<xsl:output method="text" encoding="UTF-8" indent="no"/>
	<xsl:template match="/n1:Bottles">
		<xsl:variable name="dicttypes">
			<xsl:for-each select="./n1:Dictionary" >
				<xsl:value-of select="concat(@className,';')"/>
			</xsl:for-each>
		</xsl:variable>
		<xsl:call-template name="file-preamble"/>
		<xsl:apply-templates select="n1:Namespace" mode="file-begin">
			<xsl:with-param name="indent" select="''"/>
		</xsl:apply-templates>
		<xsl:text>&#10;//pre-declaration of classes derived from VocabDictionary&#10;</xsl:text>
		<xsl:apply-templates select="n1:Dictionary" mode="predeclaration"/>
		<xsl:text>&#10;//pre-declaration of classes derived from StructBottle&#10;</xsl:text>
		<xsl:apply-templates select="n1:Struct" mode="predeclaration"/>
		<xsl:text>&#10;//pre-declaration of classes derived from WrapperBottle&#10;</xsl:text>
		<xsl:apply-templates select="n1:Wrapper" mode="predeclaration"/>
		<xsl:text>&#10;//named VectorBottles - implemented as typedefs&#10;</xsl:text>
		<xsl:apply-templates select="n1:Vector" mode="declaration">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:text>&#10;//class declarations derived from VocabDictionary&#10;</xsl:text>
		<xsl:apply-templates select="n1:Dictionary" mode="declaration"/>
		<xsl:text>&#10;//class declarations derived from StructBottle&#10;</xsl:text>
		<xsl:apply-templates select="n1:Struct" mode="declaration">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:text>&#10;//class declarations derived from WrapperBottle&#10;</xsl:text>
		<xsl:apply-templates select="n1:Wrapper" mode="declaration">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:text>&#10;//Function definitions&#10;</xsl:text>
		<xsl:apply-templates select="n1:Dictionary" mode="definition"/>
		<xsl:apply-templates select="n1:Struct" mode="definition">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Wrapper" mode="definition">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Namespace" mode="file-end"/>
	</xsl:template>
	<xsl:template name="file-preamble">
		<xsl:text>//C++ code automatically generated from YarpTypeSafeBottle XML file - do not alter</xsl:text>
		<xsl:value-of select="concat($newline,$newline,'#pragma once',$newline,$newline)"/>
		<xsl:value-of select="concat('#include &quot;TypeSafeBottle/TypeSafeBottle.h&quot;',$newline,$newline)"/>
		<xsl:value-of select="concat('using namespace darwin::msg',$seminew,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Namespace" mode="file-begin">
		<xsl:param name="indent"/>
		<xsl:value-of select="concat($indent,'namespace ',@name,' {',$newline)"/>
		<xsl:apply-templates select="n1:Namespace" mode="file-begin">
			<xsl:with-param name="indent" select="concat($indent,$tab)"/>
		</xsl:apply-templates>
	</xsl:template>
	<xsl:template match="n1:Dictionary" mode="predeclaration">
		<xsl:value-of select="concat('class ',@className,$seminew)"/>
	</xsl:template>
	<xsl:template match="n1:Struct" mode="predeclaration">
		<xsl:value-of select="concat('class ',@className,$seminew)"/>
	</xsl:template>
	<xsl:template match="n1:Wrapper" mode="predeclaration">
		<xsl:value-of select="concat('class ',@className,$seminew)"/>
	</xsl:template>
	<xsl:template match="n1:Vector" mode="declaration">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="'typedef '"/>
		<xsl:call-template name="vectorbottle-type">
			<xsl:with-param name="type" select="@valueType"/>
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:call-template>
		<xsl:value-of select="concat(' ',@className,$seminew)"/>
	</xsl:template>
	<xsl:template match="n1:Dictionary" mode="declaration">
		<xsl:value-of select="concat('class ',@className,' : public VocabDictionary {',$newline,'public:',$newline)"/>
		<xsl:apply-templates select="n1:Vocab" mode="declaration-is"/>
		<xsl:value-of select="concat($tab,'static void type_check(int);',$newline)"/>
		<xsl:value-of select="concat($tab,'static ',$stringtype,' valueStr(int);',$newline)"/>
		<xsl:value-of select="concat($tab,'enum value {',$newline)"/>
		<xsl:apply-templates select="n1:Vocab" mode="declaration-value"/>
		<xsl:value-of select="concat($tab,$tab,'unknownID = 0',$newline)"/>
		<xsl:value-of select="concat($tab,'};',$newline)"/>
		<xsl:value-of select="concat('protected:',$newline)"/>
		<xsl:value-of select="concat($tab,@className,'() {}',$seminew)"/>
		<xsl:value-of select="concat($tab,@className,'(const ',@className,'&amp;) {}',$seminew)"/>
		<xsl:value-of select="concat('};',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Struct" mode="declaration">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="concat('class ',@className,' : public StructBottle {',$newline,'public:',$newline)"/>
		<xsl:value-of select="concat($tab,@className,'()',$seminew)"/>
		<xsl:apply-templates select="n1:Variable|n1:Vector" mode="declaration-get">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Variable" mode="declaration-set">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:value-of select="concat($tab,'static void type_check(const yarp::os::Bottle*);',$newline)"/>
		<xsl:value-of select="concat('};',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Wrapper" mode="declaration">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="concat('class ',@className,' : public WrapperBottle {',$newline,'public:',$newline)"/>
		<xsl:value-of select="concat($tab,@className,'()',$seminew)"/>
		<xsl:apply-templates select="n1:Bottle" mode="declaration-get">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Bottle" mode="declaration-set">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Bottle" mode="declaration-is">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:value-of select="concat($tab,'static void type_check(const yarp::os::Bottle*);',$newline)"/>
		<xsl:apply-templates select="n1:Bottle" mode="declaration-subid">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:value-of select="concat('};',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Struct" mode="definition">
		<xsl:param name="dicttypes"/>
		<xsl:call-template name="comment-implementations">
			<xsl:with-param name="className" select="@className"/>
		</xsl:call-template>
		<xsl:apply-templates select="." mode="definition-constructor">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Variable|n1:Vector" mode="definition-get">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Variable" mode="definition-set">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="." mode="definition-type-check">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
	</xsl:template>
	<xsl:template match="n1:Wrapper" mode="definition">
		<xsl:param name="dicttypes"/>
		<xsl:call-template name="comment-implementations">
			<xsl:with-param name="className" select="@className"/>
		</xsl:call-template>
		<xsl:apply-templates select="." mode="definition-constructor">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Bottle" mode="definition-get">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Bottle" mode="definition-set">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="n1:Bottle" mode="definition-is">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:apply-templates select="." mode="definition-type-check">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
	</xsl:template>
	<xsl:template match="n1:Dictionary" mode="definition">
		<xsl:call-template name="comment-implementations">
			<xsl:with-param name="className" select="@className"/>
		</xsl:call-template>
		<xsl:apply-templates select="n1:Vocab" mode="definition-is"/>
		<xsl:apply-templates select="." mode="definition-type-check"/>
		<xsl:apply-templates select="." mode="definition-value-str"/>
	</xsl:template>
	<xsl:template match="n1:Namespace" mode="file-end">
		<xsl:apply-templates select="n1:Namespace" mode="file-end"/>
		<xsl:variable name="name" select="@name"/>
		<xsl:value-of select="concat('}',' //end namespace ',$name,$newline)"/>
	</xsl:template>
	<!--declaration templates for functions-->
	<xsl:template match="n1:Variable" mode="declaration-get">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="$tab"/>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@name"/>
			<xsl:with-param name="returntype" select="@type"/>
			<xsl:with-param name="poststr" select="' const'"/>
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:call-template>
		<xsl:value-of select="$seminew"/>
	</xsl:template>
	<xsl:template match="n1:Variable" mode="declaration-set">
		<xsl:param name="dicttypes"/>
		<xsl:choose>
			<xsl:when test="contains($builtintypes,concat(@type,';')) or contains($dicttypes,concat(@type,';'))">
				<xsl:value-of select="$tab"/>
				<xsl:call-template name="functioncall">
					<xsl:with-param name="name" select="concat('set',@name)"/>
					<xsl:with-param name="returntype" select="../@className"/>
					<xsl:with-param name="argtype" select="@type"/>
					<xsl:with-param name="dicttypes" select="$dicttypes"/>
				</xsl:call-template>
				<xsl:value-of select="$seminew"/>
			</xsl:when>
		</xsl:choose>
	</xsl:template>
	<xsl:template match="n1:Vector" mode="declaration-get">
		<xsl:param name="dicttypes"/>
		<xsl:variable name="vector">
			<xsl:call-template name="vectorbottle-type">
				<xsl:with-param name="type" select="@valueType"/>
				<xsl:with-param name="dicttypes" select="$dicttypes"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:value-of select="$tab"/>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@name"/>
			<xsl:with-param name="returntype" select="$vector"/>
			<xsl:with-param name="poststr" select="' const'"/>
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:call-template>
		<xsl:value-of select="$seminew"/>
	</xsl:template>
	<xsl:template match="n1:Bottle" mode="declaration-get">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="$tab"/>
		<xsl:if test="contains($dicttypes,concat(@valueType,';'))">
			<xsl:value-of select="$DictionaryInWrapperWarning"/>
		</xsl:if>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@subID"/>
			<xsl:with-param name="returntype" select="@valueType"/>
			<xsl:with-param name="poststr" select="' const'"/>
		</xsl:call-template>
		<xsl:value-of select="$seminew"/>
	</xsl:template>
	<xsl:template match="n1:Bottle" mode="declaration-set">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="$tab"/>
		<xsl:if test="contains($dicttypes,concat(@valueType,';'))">
			<xsl:value-of select="$DictionaryInWrapperWarning"/>
		</xsl:if>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@subID"/>
			<xsl:with-param name="returntype" select="'void'"/>
			<xsl:with-param name="argtype" select="@valueType"/>
		</xsl:call-template>
		<xsl:value-of select="$seminew"/>
	</xsl:template>
	<xsl:template match="n1:Bottle" mode="declaration-subid">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="$tab"/>
		<xsl:if test="contains($dicttypes,concat(@valueType,';'))">
			<xsl:value-of select="$DictionaryInWrapperWarning"/>
		</xsl:if>
		<xsl:value-of select="concat('typedef SubID2Type&lt;',@valueType,',VOCAB',string-length(@subID),'(')"/>
		<xsl:call-template name="vocab-macro">
			<xsl:with-param name="value" select="@subID"/>
		</xsl:call-template>
		<xsl:value-of select="concat(')&gt; ',@subID,'ID')"/>
		<xsl:value-of select="$seminew"/>
	</xsl:template>
	<xsl:template match="n1:Bottle" mode="declaration-is">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="$tab"/>
		<xsl:if test="contains($dicttypes,concat(@valueType,';'))">
			<xsl:value-of select="$DictionaryInWrapperWarning"/>
		</xsl:if>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="concat('is',@subID)"/>
			<xsl:with-param name="returntype" select="'bool'"/>
			<xsl:with-param name="poststr" select="' const'"/>
		</xsl:call-template>
		<xsl:value-of select="$seminew"/>
	</xsl:template>
	<xsl:template match="n1:Vocab" mode="declaration-value">
		<xsl:value-of select="concat($tab,$tab,@value,'ID = VOCAB',string-length(@value),'(')"/>
		<xsl:call-template name="vocab-macro">
			<xsl:with-param name="value" select="@value"/>
		</xsl:call-template>
		<xsl:value-of select="concat(')',',',$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Vocab" mode="declaration-is">
		<xsl:value-of select="concat($tab,'static ')"/>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="concat('is',@value)"/>
			<xsl:with-param name="returntype" select="'bool'"/>
			<xsl:with-param name="argtype" select="'int'"/>
		</xsl:call-template>
		<xsl:value-of select="$seminew"/>
	</xsl:template>
	<!--definition templates for functions-->
	<xsl:template match="n1:Struct" mode="definition-constructor">
		<xsl:param name="dicttypes"/>
		<xsl:text>inline </xsl:text>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@className"/>
			<xsl:with-param name="classname" select="@className"/>
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:call-template>
		<xsl:value-of select="concat(' {',$newline)"/>
		<xsl:apply-templates select="n1:Variable|n1:Vector" mode="constructor-line">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Struct" mode="definition-type-check">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="concat('inline void ',@className,'::type_check(const yarp::os::Bottle* b) {',$newline)"/>
		<xsl:value-of select="concat($tab,@className,' t;',$newline)"/>
		<xsl:value-of select="concat($tab,'StructBottle::base_type_check(&amp;t,b);',$newline)"/>
		<xsl:apply-templates select="n1:Variable|n1:Vector" mode="definition-type-check-line">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Wrapper" mode="definition-constructor">
		<xsl:text>inline </xsl:text>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@className"/>
			<xsl:with-param name="classname" select="@className"/>
		</xsl:call-template>
		<xsl:value-of select="concat(' {',$newline,$newline)"/>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Wrapper" mode="definition-type-check">
		<xsl:value-of select="concat('inline void ',@className,'::type_check(const yarp::os::Bottle* b) {',$newline)"/>
		<xsl:value-of select="concat($tab,'WrapperBottle::base_type_check(b);',$newline)"/>
		<xsl:value-of select="concat($tab,'switch (b->get(0).asVocab()) {',$newline)"/>
		<xsl:apply-templates select="n1:Bottle" mode="definition-type-check-case"/>
		<xsl:value-of select="concat($tab,'case 0:',$newline,$tab,$tab,'break;',$newline)"/>
		<xsl:value-of select="concat($tab,'default:',$newline)"/>
		<xsl:value-of select="concat($tab,$tab,'throw TypeCheckError(b,&quot;',@className,'&quot;,&quot;incorrect subID&quot;,b->get(0).asVocab());',$newline)"/>
		<xsl:value-of select="concat($tab,'}',$newline)"/>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Dictionary" mode="definition-type-check">
		<xsl:value-of select="concat('inline void ',@className,'::type_check(int v) {',$newline)"/>
		<xsl:value-of select="concat($tab,'switch (v) {',$newline)"/>
		<xsl:apply-templates select="n1:Vocab" mode="definition-type-check-case"/>
		<xsl:value-of select="concat($tab,'case unknownID:',$newline)"/>
		<xsl:value-of select="concat($tab,$tab,'break;',$newline)"/>
		<xsl:value-of select="concat($tab,'default:',$newline)"/>
		<xsl:value-of select="concat($tab,$tab,'throw TypeCheckError(&quot;',@className,'&quot;,&quot;incorrect value&quot;,v);',$newline)"/>
		<xsl:value-of select="concat($tab,'}',$newline)"/>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Dictionary" mode="definition-value-str">
		<xsl:value-of select="concat('inline ',$stringtype,' ',@className,'::valueStr(int v) {',$newline)"/>
		<xsl:value-of select="concat($tab,$stringtype,' returnval = &quot;&quot;;',$newline)"/>
		<xsl:value-of select="concat($tab,'try {',$newline)"/>
		<xsl:value-of select="concat($tab,$tab,@className,'::type_check(v);',$newline)"/>
		<xsl:value-of select="concat($tab,$tab,'returnval = VocabDictionary::base_valueStr(v);',$newline)"/>
		<xsl:value-of select="concat($tab,'}',$newline)"/>
		<xsl:value-of select="concat($tab,'catch (TypeCheckError&amp;) {',$newline)"/>
		<xsl:value-of select="concat($tab,$tab,$seminew)"/>
		<xsl:value-of select="concat($tab,'}',$newline)"/>
		<xsl:value-of select="concat($tab,'return returnval;',$newline)"/>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Variable" mode="definition-get">
		<xsl:param name="dicttypes"/>
		<xsl:text>inline </xsl:text>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@name"/>
			<xsl:with-param name="returntype" select="@type"/>
			<xsl:with-param name="classname" select="../@className"/>
			<xsl:with-param name="poststr" select="' const {'"/>
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:call-template>
		<xsl:value-of select="$newline"/>
		<xsl:apply-templates select="." mode="get-body">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Vector" mode="definition-get">
		<xsl:param name="dicttypes"/>
		<xsl:variable name="vector">
			<xsl:call-template name="vectorbottle-type">
				<xsl:with-param name="type" select="@valueType"/>
				<xsl:with-param name="dicttypes" select="$dicttypes"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:text>inline </xsl:text>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@name"/>
			<xsl:with-param name="returntype" select="$vector"/>
			<xsl:with-param name="classname" select="../@className"/>
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
			<xsl:with-param name="poststr" select="' const {'"/>
		</xsl:call-template>
		<xsl:value-of select="$newline"/>
		<xsl:apply-templates select="." mode="get-body">
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:apply-templates>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Variable" mode="definition-set">
		<xsl:param name="dicttypes"/>
		<xsl:choose>
			<xsl:when test="contains($builtintypes,concat(@type,';')) or contains($dicttypes,concat(@type,';'))">
				<xsl:text>inline </xsl:text>
				<xsl:call-template name="functioncall">
					<xsl:with-param name="name" select="concat('set',@name)"/>
					<xsl:with-param name="returntype" select="../@className"/>
					<xsl:with-param name="argtype" select="@type"/>
					<xsl:with-param name="varname" select="'v'"/>
					<xsl:with-param name="classname" select="../@className"/>
					<xsl:with-param name="dicttypes" select="$dicttypes"/>
				</xsl:call-template>
				<xsl:value-of select="concat(' {',$newline)"/>
				<xsl:apply-templates select="." mode="set-body">
					<xsl:with-param name="dicttypes" select="$dicttypes"/>
				</xsl:apply-templates>
				<xsl:value-of select="concat('}',$newline,$newline)"/>
			</xsl:when>
		</xsl:choose>
	</xsl:template>
	<xsl:template match="n1:Bottle" mode="definition-get">
		<xsl:param name="dicttypes"/>
		<xsl:text>inline </xsl:text>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@subID"/>
			<xsl:with-param name="returntype" select="@valueType"/>
			<xsl:with-param name="classname" select="../@className"/>
			<xsl:with-param name="poststr" select="' const {'"/>
		</xsl:call-template>
		<xsl:value-of select="$newline"/>
		<xsl:value-of select="concat($tab,'return get(',@subID,'ID());',$newline)"/>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Bottle" mode="definition-set">
		<xsl:param name="dicttypes"/>
		<xsl:text>inline </xsl:text>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="@subID"/>
			<xsl:with-param name="returntype" select="'void'"/>
			<xsl:with-param name="argtype" select="@valueType"/>
			<xsl:with-param name="classname" select="../@className"/>
			<xsl:with-param name="varname" select="'v'"/>
		</xsl:call-template>
		<xsl:value-of select="concat(' {',$newline)"/>
		<xsl:value-of select="concat($tab,'set(v,',@subID,'ID());',$newline)"/>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Bottle" mode="definition-is">
		<xsl:param name="dicttypes"/>
		<xsl:text>inline </xsl:text>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="concat('is',@subID)"/>
			<xsl:with-param name="returntype" select="'bool'"/>
			<xsl:with-param name="classname" select="../@className"/>
			<xsl:with-param name="poststr" select="' const {'"/>
		</xsl:call-template>
		<xsl:value-of select="$newline"/>
		<xsl:value-of select="concat($tab,'return (subID() == ',../@className,'::',@subID,'ID::value);',$newline)"/>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Vocab" mode="definition-is">
		<xsl:text>inline </xsl:text>
		<xsl:call-template name="functioncall">
			<xsl:with-param name="name" select="concat('is',@value)"/>
			<xsl:with-param name="returntype" select="'bool'"/>
			<xsl:with-param name="argtype" select="'int'"/>
			<xsl:with-param name="classname" select="../@className"/>
			<xsl:with-param name="varname" select="'v'"/>
		</xsl:call-template>
		<xsl:value-of select="concat(' {',$newline)"/>
		<xsl:value-of select="concat($tab,'return (v == ',../@className,'::',@value,'ID);',$newline)"/>
		<xsl:value-of select="concat('}',$newline,$newline)"/>
	</xsl:template>
	<!--templates to add a line to the constructor of a StructBottle, one for each variable or vector-->
	<xsl:template match="n1:Variable" mode="constructor-line">
		<xsl:param name="dicttypes"/>
		<xsl:choose>
			<xsl:when test="contains($builtintypes,concat(@type,';')) or contains($dicttypes,concat(@type,';'))">
				<xsl:variable name="fn">
					<xsl:call-template name="func-append">
						<xsl:with-param name="type" select="@type"/>
						<xsl:with-param name="dicttypes" select="$dicttypes"/>
					</xsl:call-template>
				</xsl:variable>
				<xsl:variable name="dv">
					<xsl:call-template name="get-default-val">
						<xsl:with-param name="type" select="@type"/>
						<xsl:with-param name="dicttypes" select="$dicttypes"/>
					</xsl:call-template>
				</xsl:variable>
				<xsl:value-of select="concat($tab,'add',$fn,'(&quot;',@name,'&quot;,',$dv,')',$seminew)"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="concat($tab,'addlist(&quot;',@name,'&quot;); ')"/>
				<xsl:value-of select="concat(@name,'() = ',@type,'();',$newline)"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	<xsl:template match="n1:Variable|n1:Vector" mode="get-body">
		<xsl:param name="dicttypes"/>
		<xsl:variable name="lt">
			<xsl:choose>
				<xsl:when test="@valueType">
					<xsl:call-template name="vectorbottle-type">
						<xsl:with-param name="type" select="@valueType"/>
						<xsl:with-param name="dicttypes" select="$dicttypes"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="@type"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		<xsl:variable name="count" select="count(preceding-sibling::n1:Variable)+count(preceding-sibling::n1:Vector)"/>
		<xsl:variable name="fn">
			<xsl:call-template name="func-append">
				<xsl:with-param name="type" select="@type"/>
				<xsl:with-param name="dicttypes" select="$dicttypes"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:choose>
			<xsl:when test="contains($builtintypes,concat($lt,';'))">
				<xsl:value-of select="concat($tab,'return get',$fn,'(',2*$count+1,')',$seminew)"/>
			</xsl:when>
			<xsl:when test="contains($dicttypes,concat($lt,';'))">
				<xsl:value-of select="concat($tab,'return static_cast&lt;',$lt,'::value&gt;(getvocab(',2*$count+1,'))',$seminew)"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="concat($tab,'return static_cast&lt;',$lt,'&amp;&gt;(getlist(',2*$count+1,'))',$seminew)"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	<xsl:template match="n1:Variable" mode="set-body">
		<xsl:param name="dicttypes"/>
		<xsl:variable name="count" select="count(preceding-sibling::n1:Variable)+count(preceding-sibling::n1:Vector)"/>
		<xsl:variable name="fn">
			<xsl:call-template name="func-append">
				<xsl:with-param name="type" select="@type"/>
				<xsl:with-param name="dicttypes" select="$dicttypes"/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:choose>
			<xsl:when test="contains($dicttypes,concat(@type,';'))">
				<xsl:value-of select="concat($tab,@type,'::type_check(v);',$newline)"/>
			</xsl:when>
		</xsl:choose>
		<xsl:value-of select="concat($tab,'set',$fn,'(',2*$count+1,',v)',$seminew)"/>
		<xsl:value-of select="concat($tab,'return *this',$seminew)"/>
	</xsl:template>
	<xsl:template match="n1:Vector" mode="constructor-line">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="concat($tab,'addlist(&quot;',@name,'&quot;); ')"/>
		<xsl:value-of select="concat(@name,'() = ')"/>
		<xsl:call-template name="vectorbottle-type">
			<xsl:with-param name="type" select="@valueType"/>
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:call-template>
		<xsl:value-of select="concat('()',$seminew)"/>
	</xsl:template>
	<xsl:template match="n1:Variable" mode="definition-type-check-line">
		<xsl:param name="dicttypes"/>
		<xsl:variable name="count" select="count(preceding-sibling::n1:Variable)+count(preceding-sibling::n1:Vector)"/>
		<xsl:choose>
			<xsl:when test="contains($builtintypes,concat(@type,';'))">
				<xsl:value-of select="''"/>
			</xsl:when>
			<xsl:when test="contains($dicttypes,concat(@type,';'))">
				<xsl:value-of select="concat($tab,@type,'::type_check(b-&gt;get(',2*$count+1,').asVocab());',$newline)"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="concat($tab,@type,'::type_check(b-&gt;get(',2*$count+1,').asList());',$newline)"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	<xsl:template match="n1:Vector" mode="definition-type-check-line">
		<xsl:param name="dicttypes"/>
		<xsl:variable name="count" select="count(preceding-sibling::n1:Variable)+count(preceding-sibling::n1:Vector)"/>
		<xsl:value-of select="$tab"/>
		<xsl:call-template name="vectorbottle-type">
			<xsl:with-param name="type" select="@valueType"/>
			<xsl:with-param name="dicttypes" select="$dicttypes"/>
		</xsl:call-template>
		<xsl:value-of select="concat('::type_check(b-&gt;get(',2*$count+1,').asList());',$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Bottle" mode="definition-type-check-case">
		<xsl:param name="dicttypes"/>
		<xsl:value-of select="concat($tab,'case ',@subID,'ID::value:',$newline)"/>
		<xsl:value-of select="concat($tab,$tab,@valueType,'::type_check(b-&gt;get(1).asList());',$newline)"/>
		<xsl:value-of select="concat($tab,$tab,'break;',$newline)"/>
	</xsl:template>
	<xsl:template match="n1:Vocab" mode="definition-type-check-case">
		<xsl:value-of select="concat($tab,'case ',@value,'ID:',$newline)"/>
	</xsl:template>
	<!--templates to create a function call with return type, function name and argument type-->
	<xsl:template name="functioncall">
		<xsl:param name="name"/>
		<xsl:param name="argtype" select="''"/>
		<xsl:param name="returntype" select="''"/>
		<xsl:param name="varname" select="''"/>
		<xsl:param name="classname" select="''"/>
		<xsl:param name="prestr" select="''"/>
		<xsl:param name="poststr" select="''"/>
		<xsl:param name="dicttypes" select="''"/>
		<xsl:value-of select="$prestr"/>
		<xsl:choose>
			<xsl:when test="not($returntype)">
				<xsl:value-of select="''"/>
			</xsl:when>
			<xsl:when test="contains('void;bool;int;double;',concat($returntype,';'))">
				<xsl:value-of select="concat($returntype,' ')"/>
			</xsl:when>
			<xsl:when test="contains('string;',concat($returntype,';'))">
				<xsl:value-of select="concat($stringtype,' ')"/>
			</xsl:when>
			<xsl:when test="contains('vocab;',concat($returntype,';'))">
				<xsl:value-of select="concat($vocabtype,' ')"/>
			</xsl:when>
			<xsl:when test="contains($dicttypes,concat($returntype,';'))">
				<xsl:value-of select="concat($returntype,'::value ')"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="concat($returntype,'&amp; ')"/>
			</xsl:otherwise>
		</xsl:choose>
		<xsl:if test="$classname">
			<xsl:value-of select="concat($classname,'::')"/>
		</xsl:if>
		<xsl:value-of select="concat($name,'(')"/>
		<xsl:choose>
			<xsl:when test="not($argtype)">
				<xsl:value-of select="''"/>
			</xsl:when>
			<xsl:when test="contains('int;double;',concat($argtype,';'))">
				<xsl:value-of select="$argtype"/>
			</xsl:when>
			<xsl:when test="contains('string;',concat($argtype,';'))">
				<xsl:value-of select="concat('const ',$stringtype,'&amp;')"/>
			</xsl:when>
			<xsl:when test="contains('vocab;',concat($argtype,';'))">
				<xsl:value-of select="$vocabtype"/>
			</xsl:when>
			<xsl:when test="contains($dicttypes,concat($argtype,';'))">
				<xsl:value-of select="concat($argtype,'::value')"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="concat('const ',$argtype,'&amp;')"/>
			</xsl:otherwise>
		</xsl:choose>
		<xsl:if test="$varname">
			<xsl:value-of select="concat(' ',$varname)"/>
		</xsl:if>
		<xsl:value-of select="concat(')',$poststr)"/>
	</xsl:template>
	<xsl:template name="vectorbottle-type">
		<xsl:param name="type"/>
		<xsl:param name="dicttypes" select="''"/>
		<xsl:choose>
			<xsl:when test="$type = 'int'">
				<xsl:value-of select="'IntVector'"/>
			</xsl:when>
			<xsl:when test="$type = 'double'">
				<xsl:value-of select="'DoubleVector'"/>
			</xsl:when>
			<xsl:when test="$type = 'string'">
				<xsl:value-of select="'StringVector'"/>
			</xsl:when>
			<xsl:when test="$type = 'vocab'">
				<xsl:value-of select="'VocabVector'"/>
			</xsl:when>
			<xsl:when test="contains($dicttypes,concat($type,';'))">
				<xsl:value-of select="concat('DictionaryBottle&lt;',$type,'&gt;')"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="concat('VectorBottle&lt;',$type,'&gt;')"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	<!--recursive template to tokenize a vocab for the yarp::os::VOCAB macros-->
	<xsl:template name="vocab-macro">
		<xsl:param name="value"/>
		<xsl:variable name="letter" select="substring($value,1,1)"/>
		<xsl:text>'</xsl:text>
		<xsl:value-of select="$letter"/>
		<xsl:text>'</xsl:text>
		<xsl:if test="string-length($value) &gt; 1">
			<xsl:value-of select="','"/>
			<xsl:call-template name="vocab-macro">
				<xsl:with-param name="value" select="substring($value,2)"/>
			</xsl:call-template>
		</xsl:if>
	</xsl:template>
	<xsl:template name="comment-implementations">
		<xsl:param name="className"/>
		<xsl:value-of select="concat('/*========================================',$newline)"/>
		<xsl:value-of select="concat('* ',$className,' member function implementations',$newline)"/>
		<xsl:value-of select="concat('*=======================================*/',$newline,$newline)"/>
	</xsl:template>
	<!--some variable used throughout the document-->
	<xsl:template name="func-append">
		<xsl:param name="type"/>
		<xsl:param name="dicttypes" select="''"/>
		<xsl:choose>
			<xsl:when test="contains($builtintypes,concat($type,';'))">
				<xsl:value-of select="$type"/>
			</xsl:when>
			<xsl:when test="contains($dicttypes,concat($type,';'))">
				<xsl:value-of select="'vocab'"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="'list'"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>
	<xsl:template name="get-default-val">
		<xsl:param name="type"/>
		<xsl:param name="dicttypes" select="''"/>
		<xsl:choose>
			<xsl:when test="$type = 'int'">
				<xsl:value-of select="'0'"/>
			</xsl:when>
			<xsl:when test="$type = 'double'">
				<xsl:value-of select="'0.0'"/>
			</xsl:when>
			<xsl:when test="$type = 'string'">
				<xsl:text>&quot;&quot;</xsl:text>
			</xsl:when>
			<xsl:when test="$type = 'vocab'">
				<xsl:value-of select="'0'"/>
			</xsl:when>
			<xsl:when test="contains($dicttypes,concat($type,';'))">
				<xsl:value-of select="concat($type,'::unknownID')"/>
			</xsl:when>
		</xsl:choose>
	</xsl:template>
	<xsl:variable name="builtintypes">
		<xsl:value-of select="'int;double;string;vocab;'"/>
	</xsl:variable>
	<xsl:variable name="stringtype">
		<xsl:value-of select="'yarp::os::ConstString'"/>
	</xsl:variable>
	<xsl:variable name="vocabtype">
		<xsl:value-of select="'int'"/>
	</xsl:variable>
	<xsl:variable name="seminew">
		<xsl:value-of select="concat(';',$newline)"/>
	</xsl:variable>
	<xsl:variable name="newline">
		<xsl:value-of select="'&#10;'"/>
	</xsl:variable>
	<xsl:variable name="tab">
		<xsl:value-of select="'&#09;'"/>
	</xsl:variable>
	<xsl:variable name="DictionaryInWrapperWarning">
		<xsl:value-of select="'A DICTIONARY IS NOT ALLOWED AS VALUETYPE FOR A WRAPPER '"/>
	</xsl:variable>
</xsl:transform>
