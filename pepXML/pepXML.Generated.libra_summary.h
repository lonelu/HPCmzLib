﻿#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace pepXML { namespace Generated { class libra_summaryFragment_masses; } }
namespace pepXML { namespace Generated { class libra_summaryContributing_channel; } }

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
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://regis-web.systemsbiology.net/pepXML")][System.Xml.Serialization.XmlRootAttribute(Namespace = "http://regis-web.systemsbiology.net/pepXML", IsNullable = false)] public partial class libra_summary
        class libra_summary
        {

        private:
            std::vector<libra_summaryFragment_masses*> fragment_massesField;

            std::vector<libra_summaryContributing_channel*> isotopic_contributionsField;

            float mass_toleranceField = 0;

            int centroiding_preferenceField = 0;

            int normalizationField = 0;

            int output_typeField = 0;

            std::string channel_codeField;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("fragment_masses")] public libra_summaryFragment_masses[] fragment_masses
            std::vector<libra_summaryFragment_masses*> getfragment_masses() const;
            void setfragment_masses(const std::vector<libra_summaryFragment_masses*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlArrayItemAttribute("contributing_channel", IsNullable = false)] public libra_summaryContributing_channel[] isotopic_contributions
            std::vector<libra_summaryContributing_channel*> getisotopic_contributions() const;
            void setisotopic_contributions(const std::vector<libra_summaryContributing_channel*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float mass_tolerance
            float getmass_tolerance() const;
            void setmass_tolerance(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public int centroiding_preference
            int getcentroiding_preference() const;
            void setcentroiding_preference(int value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public int normalization
            int getnormalization() const;
            void setnormalization(int value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public int output_type
            int getoutput_type() const;
            void setoutput_type(int value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string channel_code
            std::string getchannel_code() const;
            void setchannel_code(const std::string &value);
        };
    }
}
