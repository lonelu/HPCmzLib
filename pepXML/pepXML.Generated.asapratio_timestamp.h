﻿#pragma once

#include <string>

//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.42000
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------


namespace pepXML
{
    namespace Generated
    {
        /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://regis-web.systemsbiology.net/pepXML")][System.Xml.Serialization.XmlRootAttribute(Namespace = "http://regis-web.systemsbiology.net/pepXML", IsNullable = false)] public partial class asapratio_timestamp
        class asapratio_timestamp
        {

        private:
            std::string quant_label_massesField;

            std::string static_quant_labelField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string quant_label_masses
            std::string getquant_label_masses() const;
            void setquant_label_masses(const std::string &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string static_quant_label
            std::string getstatic_quant_label() const;
            void setstatic_quant_label(const std::string &value);
        };
    }
}
