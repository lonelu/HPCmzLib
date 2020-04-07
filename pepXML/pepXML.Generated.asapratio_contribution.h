﻿#pragma once

#include <string>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace pepXML { namespace Generated { class asapratio_lc_lightpeak; } }
namespace pepXML { namespace Generated { class asapratio_lc_heavypeak; } }

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
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://regis-web.systemsbiology.net/pepXML")][System.Xml.Serialization.XmlRootAttribute(Namespace = "http://regis-web.systemsbiology.net/pepXML", IsNullable = false)] public partial class asapratio_contribution
        class asapratio_contribution
        {

        private:
            pepXML::Generated::asapratio_lc_lightpeak *asapratio_lc_lightpeakField;

            pepXML::Generated::asapratio_lc_heavypeak *asapratio_lc_heavypeakField;

            float ratioField = 0;

            float errorField = 0;

            std::string chargeField;

            unsigned char useField = 0;

            /// <remarks/>
        public:
            virtual ~asapratio_contribution()
            {
                delete asapratio_lc_lightpeakField;
                delete asapratio_lc_heavypeakField;
            }

            pepXML::Generated::asapratio_lc_lightpeak *getasapratio_lc_lightpeak() const;
            void setasapratio_lc_lightpeak(pepXML::Generated::asapratio_lc_lightpeak *value);

            /// <remarks/>
            pepXML::Generated::asapratio_lc_heavypeak *getasapratio_lc_heavypeak() const;
            void setasapratio_lc_heavypeak(pepXML::Generated::asapratio_lc_heavypeak *value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float ratio
            float getratio() const;
            void setratio(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float error
            float geterror() const;
            void seterror(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute(DataType = "nonNegativeInteger")] public string charge
            std::string getcharge() const;
            void setcharge(const std::string &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public byte use
            unsigned char getuse() const;
            void setuse(unsigned char value);
        };
    }
}
