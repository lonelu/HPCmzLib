﻿#pragma once

#include <string>
#include <vector>

//C# TO C++ CONVERTER NOTE: Forward class declarations:
namespace pepXML { namespace Generated { class peptideprophet_summaryMixture_modelMixturemodelPoint; } }

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
//ORIGINAL LINE: [System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "4.7.2046.0")][System.SerializableAttribute()][System.Diagnostics.DebuggerStepThroughAttribute()][System.ComponentModel.DesignerCategoryAttribute("code")][System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true, Namespace = "http://regis-web.systemsbiology.net/pepXML")] public partial class peptideprophet_summaryMixture_modelMixturemodel
        class peptideprophet_summaryMixture_modelMixturemodel
        {

        private:
            std::vector<peptideprophet_summaryMixture_modelMixturemodelPoint*> pointField;

            std::string nameField;

            float pos_bandwidthField = 0;

            float neg_bandwidthField = 0;

            /// <remarks/>
        public:
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlElementAttribute("point")] public peptideprophet_summaryMixture_modelMixturemodelPoint[] point
            std::vector<peptideprophet_summaryMixture_modelMixturemodelPoint*> getpoint() const;
            void setpoint(const std::vector<peptideprophet_summaryMixture_modelMixturemodelPoint*> &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public string name
            std::string getname() const;
            void setname(const std::string &value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float pos_bandwidth
            float getpos_bandwidth() const;
            void setpos_bandwidth(float value);

            /// <remarks/>
//C# TO C++ CONVERTER NOTE: The following .NET attribute has no direct equivalent in C++:
//ORIGINAL LINE: [System.Xml.Serialization.XmlAttributeAttribute()] public float neg_bandwidth
            float getneg_bandwidth() const;
            void setneg_bandwidth(float value);
        };
    }
}
