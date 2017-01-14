<?xml version="1.0" encoding="UTF-8"?> 
<java version="1.6.0_29" class="java.beans.XMLDecoder"> 
 <object class="com.ti.dvt.datamodel.core.DataModel"> 
  <void property="filePath"> 
   <string>C:\scm\svn\trunk\dvt_resources\platform\CCS\dvt\solutions\CCSgraphs\FFTWaterfall</string> 
  </void> 
  <void method="addSource"> 
   <object class="com.ti.dvt.datamodel.ccsgraphs.CCSGraphsJtagDataSource"> 
    <void method="connectOutput"> 
     <object class="com.ti.dvt.datamodel.ccsgraphs.FFTCCSGraphDecoder"> 
      <void method="connectOutput"> 
       <object class="com.ti.dvt.datamodel.ccsgraphs.GraphScaleDecoder"> 
        <void method="connectOutput"> 
         <object class="com.ti.dvt.datamodel.core.CircularBuffer"> 
          <void property="name"> 
           <string>CircularBuffer</string> 
          </void> 
          <void property="size"> 
           <int>160</int> 
          </void> 
         </object> 
        </void> 
        <void property="graphType"> 
         <string>FFT Waterfall</string> 
        </void> 
        <void property="name"> 
         <string>GraphScaleDecoder</string> 
        </void> 
       </object> 
      </void> 
      <void property="fftFrameSize"> 
       <int>16</int> 
      </void> 
      <void property="fftOrder"> 
       <int>4</int> 
      </void> 
      <void property="graphType"> 
       <string>FFT Waterfall</string> 
      </void> 
      <void property="name"> 
       <string>FFTCCSGraphDecoder</string> 
      </void> 
     </object> 
    </void> 
    <void property="blockSize1"> 
     <int>16</int> 
    </void> 
    <void property="blockSize2"> 
     <int>16</int> 
    </void> 
    <void property="graphType"> 
     <string>FFT Waterfall</string> 
    </void> 
    <void property="name"> 
     <string>CCSGraphsJtagDataSource</string> 
    </void> 
   </object> 
  </void> 
 </object> 
</java> 
