.. _mqtt_google_cloud:

nRF9160: MQTT Google Cloud
#####################
This application gathers readings from a Bosch BME680 environmental sensor and publishes to a GCP Pub/Sub topic.

Overview
********
The application gathers data in an array of size set in prj.conf. When full, it establishes a TLS session, authenticates with GC IoT Core and publishes data.

Requirements
************
* Google Cloud SDK <https://cloud.google.com/sdk/docs/#install_the_latest_cloud_tools_version_cloudsdk_current_version>
* Python 3
* Segger J-Link debugger

.. include:: /includes/boardname_tables/sample_boardnames.txt
   :start-after: set5_start
   :end-before: set5_end

.. include:: /includes/spm.txt

Dependencies
************
* nrf-sdk v1.3 or newer - tracks master <https://github.com/nrfconnect/sdk-nrf/tree/v1.3-branch>
* nRF91 modem firmware v1.2 <https://www.nordicsemi.com/-/media/Software-and-other-downloads/Dev-Kits/nRF9160-DK/nRF9160-modem-FW/mfwnrf9160120.zip>

References
**********
gcloud library is based on:
<https://devzone.nordicsemi.com/cfs-file/__key/telligent-evolution-components-attachments/01-27-00-00-00-00-12-59/nRF9160DKtoGoogleCloud.zip>
modified for use with new ncs mqtt bindings and compatibility with Thingy91.
