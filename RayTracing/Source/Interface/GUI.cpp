#include "stdafx.h"
#include "GUI.h"

#include "Graphics/Application/Renderer.h"
#include "Graphics/Core/LiDARSimulation.h"

/// Initialization of static attributes

const unsigned GUI::MAX_RETURN = 10;
const unsigned GUI::MIN_RETURN = 1;

/// [Protected methods]

GUI::GUI() :
	_customClasses(nullptr), _lidarClasses(nullptr), _showLidarSettings(false), _showLidarASPRSClasses(false),_showLidarCustomClasses(false), _showRenderingSettings(false), 
	_showSceneSettings(false), _showScreenshotSettings(false), _showAboutUs(false), _showControls(false)
{
	_lidarParams = LiDARSimulation::getLiDARParams();
	_pointCloudParams = LiDARSimulation::getPointCloudParams();
	_renderer = Renderer::getInstance();	
	_renderingParams = Renderer::getInstance()->getRenderingParameters();
}

void GUI::createMainLayout()
{
}

void GUI::createMenu()
{
	ImGuiIO& io = ImGui::GetIO();
	unsigned int flags = 0;

	if (_showRenderingSettings) showRenderingSettings();
	if (_showLidarSettings) showLiDARSettings();
	if (_showScreenshotSettings) showScreenshotSettings();
	if (_showSceneSettings) showSceneSettings();
	if (_showLidarASPRSClasses) showLiDARASPRSClasses();
	if (_showLidarCustomClasses) showLiDARCustomClasses();
	if (_showPointCloudSettings) showPointCloudSettings();
	if (_showAboutUs) showAboutUsWindow();
	if (_showControls) showControls();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			ImGui::MenuItem("Rendering", NULL, &_showRenderingSettings);
			ImGui::MenuItem("Screenshot", NULL, &_showScreenshotSettings);
			ImGui::MenuItem("LiDAR", NULL, &_showLidarSettings);
			ImGui::MenuItem("Scene", NULL, &_showSceneSettings);
			ImGui::MenuItem("Save Point Cloud", NULL, &_showPointCloudSettings);
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Help"))
		{
			ImGui::MenuItem("About the project", NULL, &_showAboutUs);
			ImGui::MenuItem("Controls", NULL, &_showControls);
			ImGui::EndMenu();
		}

		ImGui::SameLine();
		ImGui::SetCursorPosX(io.DisplaySize.x - 250);

		ImGui::Checkbox("Lock camera", &_renderingParams->_lockCamera);
		ImGui::SameLine(); 
		this->renderHelpMarker("Avoids some movements to also modify the camera parameters");
		
		ImGui::SameLine(0, 20);
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::EndMainMenuBar();
	}

	this->createMainLayout();
}

void GUI::leaveSpace(const unsigned numSlots)
{
	for (int i = 0; i < numSlots; ++i)
	{
		ImGui::Spacing();
	}
}

void GUI::renderHelpMarker(const char* message)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(message);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

void GUI::showAboutUsWindow()
{
	if (ImGui::Begin("About the project", &_showAboutUs))
	{
		ImGui::Text("This code belongs to a research project from University of Jaén (GGGJ group).");	
	}

	ImGui::End();
}

void GUI::showAerialTabItem()
{
	LiDARScene* scene = Renderer::getInstance()->getCurrentScene();
	LinearInterpolation* lidarPath = Renderer::getInstance()->getCurrentScene()->getLiDARSimulation()->getAerialPath();
	ImDrawList* drawList = ImGui::GetWindowDrawList();

	if (ImGui::BeginTabItem("Aerial LiDAR"))
	{
		std::vector<vec4>* points = lidarPath->getWaypoints();
		static bool addLine = false;

		this->leaveSpace(3);

		ImGui::SliderFloat("LiDAR height", &_lidarParams->_aerialPosition.y, -1.0f, 8.0f);

		this->leaveSpace(2);
		ImGui::Separator();
		this->leaveSpace(2);

		// Background
		ImVec2 canvasPos = ImGui::GetCursorScreenPos();            // ImDrawList API uses screen coordinates!
		ImVec2 canvasSize = ImGui::GetContentRegionAvail();        // Resize canvas to what's available
		if (canvasSize.x < 50.0f) canvasSize.x = 50.0f;
		if (canvasSize.y < 50.0f) canvasSize.y = 50.0f;
		drawList->AddRectFilled(canvasPos, ImVec2(canvasPos.x + canvasSize.x, canvasPos.y + canvasSize.y), IM_COL32(28, 28, 28, 255));
		drawList->AddRect(canvasPos, ImVec2(canvasPos.x + canvasSize.x, canvasPos.y + canvasSize.y), IM_COL32(200, 200, 200, 255));
		drawList->PushClipRect(canvasPos, ImVec2(canvasPos.x + canvasSize.x, canvasPos.y + canvasSize.y), true);      // Clip lines within the canvas (if we resize it, etc.)

		for (int i = 0; i < (int)_lidarPath.size() - 1; i += 1)
		{
			drawList->AddLine(ImVec2(canvasPos.x + _lidarPath[i].x, canvasPos.y + _lidarPath[i].y),
							   ImVec2(canvasPos.x + _lidarPath[i + 1].x, canvasPos.y + _lidarPath[i + 1].y),
							   IM_COL32(255, 255, 0, 255), 2.0f);
		}

		drawList->PopClipRect();

		ImGui::EndTabItem();
	}
}

void GUI::showControls()
{
	if (ImGui::Begin("Scene controls", &_showControls))
	{
		ImGui::Columns(2, "ControlColumns"); // 4-ways, with border
		ImGui::Separator();
		ImGui::Text("Movement"); ImGui::NextColumn();
		ImGui::Text("Control"); ImGui::NextColumn();
		ImGui::Separator();

		const int NUM_MOVEMENTS = 14;
		const char* movement[] = { "Orbit (XZ)", "Undo Orbit (XZ)", "Orbit (Y)", "Undo Orbit (Y)", "Dolly", "Truck", "Boom", "Crane", "Reset Camera", "Take Screenshot", "Continue Animation", "Zoom +/-", "Pan", "Tilt" };
		const char* controls[] = { "X", "Ctrl + X", "Y", "Ctrl + Y", "W, S", "D, A", "Up arrow", "Down arrow", "R", "K", "I", "Scroll wheel", "Move mouse horizontally(hold button)", "Move mouse vertically (hold button)" };

		for (int i = 0; i < NUM_MOVEMENTS; i++)
		{
			ImGui::Text(movement[i]); ImGui::NextColumn();
			ImGui::Text(controls[i]); ImGui::NextColumn();
		}

		ImGui::Columns(1);
		ImGui::Separator();

	}

	ImGui::End();
}

void GUI::showLandTabItem()
{
	LiDARScene* scene = Renderer::getInstance()->getCurrentScene();
	AABB aabb = scene->getAABB();
	vec3 min = aabb.min(), max = aabb.max();

	if (ImGui::BeginTabItem("Terrestrial LiDAR"))
	{
		this->leaveSpace(3);

		ImGui::SliderFloat3("Position", &_lidarParams->_landPosition[0], glm::min(min.x, glm::min(min.y, min.z)) - 2.0f, glm::max(max.x, glm::max(max.y, max.z)) + 2.0f);

		ImGui::EndTabItem();
	}
}

void GUI::showLiDARASPRSClasses()
{
	if (ImGui::Begin("ASPRS classes", &_showLidarASPRSClasses))
	{
		ImGui::BeginChild("ASPRSClassList");

		if (!_lidarClasses)
		{
			_lidarClasses = Model3D::getASPRSClasses();
		}

		int id = 0;
		for (auto pair : *_lidarClasses)
		{
			ImGui::Text(pair.first.c_str());

			ImGui::SameLine(150.0f);

			ImGui::PushID(id++);
			const char* label = "          ";
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(pair.second.x, pair.second.y, pair.second.z));
			ImGui::Button(label);
			ImGui::PopStyleColor(1);
			ImGui::PopID();
		}

		ImGui::EndChild();
	}

	ImGui::End();
}

void GUI::showLiDARCustomClasses()
{
	if (ImGui::Begin("Custom classes", &_showLidarCustomClasses))
	{
		ImGui::BeginChild("CustomClassList");

		if (!_customClasses)
		{
			_customClasses = Model3D::getCustomClasses();
		}

		int id = 0;
		for (auto pair : *_customClasses)
		{
			ImGui::Text(pair.first.c_str());
			
			ImGui::SameLine(150.0f);

			ImGui::PushID(id++);
			const char* label = "          ";
			ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(pair.second.x, pair.second.y, pair.second.z));
			ImGui::Button(label);
			ImGui::PopStyleColor(1);
			ImGui::PopID();
		}

		ImGui::EndChild();	
	}

	ImGui::End();
}

void GUI::showLiDARSettings()
{
	if (ImGui::Begin("LiDAR Settings", &_showLidarSettings))
	{
		for (int i = 0; i < 2; i++) ImGui::Spacing();

		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(1 / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(1 / 7.0f, 0.8f, 0.8f));

		if (ImGui::Button("Start simulation"))
		{
			_renderer->getCurrentScene()->launchSimulation();
		}

		ImGui::PopStyleColor(3);
		ImGui::PopID();

		ImGui::SameLine(0, 100);

		if (ImGui::Button("Show custom classes"))
		{
			_showLidarCustomClasses = true;
		}

		ImGui::SameLine();

		if (ImGui::Button("Show LiDAR classes"))
		{
			_showLidarASPRSClasses = true;
		}

		for (int i = 0; i < 4; i++) ImGui::Spacing();
		
		if (ImGui::BeginTabBar("LiDARTabBar"))
		{
			this->showLiDARTabItem();
			this->showAerialTabItem();
			this->showLandTabItem();

			ImGui::EndTabBar();
		}
	}

	ImGui::End();
}

void GUI::showLiDARTabItem()
{
	float min_f = .0f, min2_f = 0.97f, max_f = 1.0f, max2_f = 5.0f;

	if (ImGui::BeginTabItem("General"))
	{
		this->leaveSpace(3);

		const char* lidarTypeTitles[] = { "Aerial", "Terrestrial" };
		ImGui::Combo("LiDAR Type", &_lidarParams->_lidarType, lidarTypeTitles, IM_ARRAYSIZE(lidarTypeTitles));	

		this->leaveSpace(2);

		ImGui::SliderScalar("Number of rays", ImGuiDataType_U32, &_lidarParams->_numRays, &LiDARParameters::MIN_NUMBER_OF_RAYS, &LiDARParameters::MAX_NUMBER_OF_RAYS);
		ImGui::SliderScalar("Maximum number of returns", ImGuiDataType_U8, &_lidarParams->_maxReturns, &MIN_RETURN, &MAX_RETURN);

		this->leaveSpace(2);

		if (ImGui::CollapsingHeader("Random noise"))
		{
			this->leaveSpace(2);

			ImGui::SliderScalar("Outlier threshold", ImGuiDataType_Float, &_lidarParams->_outlierThreshold, &min2_f, &max_f);
			ImGui::SliderScalar("Outlier displacement", ImGuiDataType_Float, &_lidarParams->_outlierDisplacement, &min_f, &max2_f);

			this->leaveSpace(2);
		}

		if (ImGui::CollapsingHeader("Return success"))
		{
			this->leaveSpace(2);

			std::string successMessage = "Success percentage of return ";
			for (int i = 0; i < _lidarParams->_maxReturns; ++i)
			{
				ImGui::SliderScalar((successMessage + std::to_string(i)).c_str(), ImGuiDataType_Float, &_lidarParams->_successPercentage[i], &min_f, &max_f);
			}

			this->leaveSpace(2);
		}

		if (ImGui::CollapsingHeader("Range"))
		{
			this->leaveSpace(2);

			ImGui::SliderFloat("Maximum travelling time (ns)", &_lidarParams->_maximumTravellingTime, 1.0f, 300.0f);
			ImGui::SliderFloat("Y offset", &_lidarParams->_yOffset, .0f, glm::pi<float>() / 3.0f);
			ImGui::SliderFloat("Z offset", &_lidarParams->_zOffset, .0f, glm::pi<float>() / 3.0f);

			this->leaveSpace(2);
		}

		if (ImGui::CollapsingHeader("Surface properties"))
		{
			this->leaveSpace(2);

			ImGui::Text("Shiny surface");
			ImGui::Separator();
			ImGui::SliderFloat("Shiny surface translation (base)", &_lidarParams->_shininessTranslation, .0f, 50.0f);
			ImGui::SliderFloat("Error weight (linked to model)", &_lidarParams->_shininessRandWeight, .0f, 50.0f);

			this->leaveSpace(2);

			ImGui::Text("Water");
			ImGui::Separator();
			ImGui::Checkbox("Bathymetric LiDAR", &_lidarParams->_bathymetric);

			this->leaveSpace(2);
		}

		if (ImGui::CollapsingHeader("Intensity"))
		{
			this->leaveSpace(2);

			ImGui::SliderFloat("Distance weight", &_lidarParams->_distanceWeight, glm::epsilon<float>(), .1f);
			ImGui::SliderFloat("Incidence angle weight", &_lidarParams->_incidenceAngleWeight, glm::epsilon<float>(), .1f);

			this->leaveSpace(2);
		}

		if (ImGui::CollapsingHeader("Errors induced by terrain slope"))
		{
			this->leaveSpace(2);

			ImGui::Checkbox("Horizontal error", &_lidarParams->_moveTerrainHorizontally);
			ImGui::Checkbox("Vertical error", &_lidarParams->_moveTerrainVertically);

			this->leaveSpace(2);
		}

		ImGui::EndTabItem();
	}
}

void GUI::showPointCloudSettings()
{
	if (ImGui::Begin("Point Cloud File", &_showPointCloudSettings, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::InputText("Filename", _pointCloudParams->_filenameBuffer, IM_ARRAYSIZE(_pointCloudParams->_filenameBuffer));
		ImGui::Checkbox("Save point cloud after simulation", &_pointCloudParams->_savePointCloud);
	}

	ImGui::End();
}

void GUI::showScreenshotSettings()
{
	if (ImGui::Begin("Screenshot Settings", &_showScreenshotSettings, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::SliderFloat("Size multiplier", &_renderingParams->_screenshotMultiplier, 1.0f, 10.0f);
		ImGui::InputText("Filename", _renderingParams->_screenshotFilenameBuffer, IM_ARRAYSIZE(_renderingParams->_screenshotFilenameBuffer));

		this->leaveSpace(2);

		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(1 / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(1 / 7.0f, 0.8f, 0.8f));

		if (ImGui::Button("Take screenshot"))
		{
			std::string filename = _renderingParams->_screenshotFilenameBuffer;

			if (filename.empty())
			{
				filename = "Screenshot.png";
			}
			else if (filename.find(".png") == std::string::npos)
			{
				filename += ".png";
			}

			Renderer::getInstance()->getScreenshot(filename);
		}

		ImGui::PopStyleColor(3);
		ImGui::PopID();
	}

	ImGui::End();
}

void GUI::showRenderingSettings()
{
	if (ImGui::Begin("Rendering Settings", &_showRenderingSettings))
	{
		ImGui::ColorEdit3("Background color", &_renderingParams->_backgroundColor[0]); 

		this->leaveSpace(3);

		if (ImGui::BeginTabBar("LiDARTabBar"))
		{
			if (ImGui::BeginTabItem("General settings"))
			{
				this->leaveSpace(1);

				ImGui::Separator();
				ImGui::Text("Lighting");

				ImGui::SliderFloat("Scattering", &_renderingParams->_materialScattering, 0.0f, 1.0f);

				this->leaveSpace(2);

				ImGui::Separator();
				ImGui::Text("Scenario");

				ImGui::Checkbox("Render scenario", &_renderingParams->_showTriangleMesh);

				{
					ImGui::Spacing();

					ImGui::NewLine();
					ImGui::SameLine(30, 0);
					ImGui::Checkbox("Screen Space Ambient Occlusion", &_renderingParams->_ambientOcclusion);

					ImGui::NewLine();
					ImGui::SameLine(30, 0);
					ImGui::Checkbox("Render semantic concepts", &_renderingParams->_renderSemanticConcept);

					{
						ImGui::SameLine(0, 30);
						ImGui::RadioButton("Custom class", &_renderingParams->_semanticRenderingConcept, RenderingParameters::CUSTOM_CONCEPT); ImGui::SameLine();
						ImGui::RadioButton("ASPRS class", &_renderingParams->_semanticRenderingConcept, RenderingParameters::ASPRS_CONCEPT);
					}

					const char* visualizationTitles[] = { "Points", "Lines", "Triangles", "All" };
					ImGui::NewLine();
					ImGui::SameLine(30, 0);
					ImGui::Combo("Visualization", &_renderingParams->_visualizationMode, visualizationTitles, IM_ARRAYSIZE(visualizationTitles));

					ImGui::Spacing();
				}

				ImGui::Checkbox("Render liDAR point cloud", &_renderingParams->_showLidarPointCloud);
				ImGui::NewLine(); ImGui::SameLine(30, 0); ImGui::RadioButton("Uniform", &_renderingParams->_pointCloudType, RenderingParameters::UNIFORM);
				ImGui::NewLine(); ImGui::SameLine(30, 0); ImGui::RadioButton("Height", &_renderingParams->_pointCloudType, RenderingParameters::HEIGHT);
				ImGui::SameLine(0, 47);
				ImGui::Checkbox("Grayscale", &_renderingParams->_grayscaleHeight);
				ImGui::NewLine(); ImGui::SameLine(30, 0); ImGui::RadioButton("RGB", &_renderingParams->_pointCloudType, RenderingParameters::SHADOWED);
				ImGui::NewLine(); ImGui::SameLine(30, 0); ImGui::RadioButton("Custom semantic concept", &_renderingParams->_pointCloudType, RenderingParameters::CUSTOM_SEMANTIC);
				ImGui::NewLine(); ImGui::SameLine(30, 0); ImGui::RadioButton("ASPRS semantic concept", &_renderingParams->_pointCloudType, RenderingParameters::ASPRS_SEMANTIC);
				ImGui::NewLine(); ImGui::SameLine(30, 0); ImGui::RadioButton("Return number", &_renderingParams->_pointCloudType, RenderingParameters::RETURN_NUMBER);
				ImGui::NewLine(); ImGui::SameLine(30, 0); ImGui::RadioButton("Intensity", &_renderingParams->_pointCloudType, RenderingParameters::INTENSITY);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("LiDAR related"))
			{
				this->leaveSpace(1);

				ImGui::Checkbox("Render LiDAR model", &_renderingParams->_showLidarModel);
				ImGui::SameLine(0, 15);
				ImGui::Text("(Render basic scene must be enabled)");
				ImGui::Checkbox("Render LiDAR rays", &_renderingParams->_showLidarRays);
				ImGui::SameLine();
				ImGui::SliderFloat("Ray percentage", &_renderingParams->_raysPercentage, 0.0f, 1.0f);
				ImGui::Checkbox("Render LiDAR aerial path", &_renderingParams->_showLidarAerialPath);

				// Return rendering
				float min_f = .0f, max_f = 1.0f;
				this->leaveSpace(2);
				ImGui::SliderScalar("First return rendered", ImGuiDataType_U8, &_lidarParams->_lastReturnRendered, &MIN_RETURN, &_lidarParams->_maxReturns);
				ImGui::SliderScalar("Return / Number of returns", ImGuiDataType_Float, &_lidarParams->_returnDivisionFilter, &min_f, &max_f);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Data structures"))
			{
				this->leaveSpace(1);

				ImGui::Checkbox("Render BVH", &_renderingParams->_showBVH);

				{
					this->leaveSpace(1);

					ImGui::NewLine(); ImGui::SameLine(0, 22);
					ImGui::ColorEdit3("BVH color", &_renderingParams->_bvhWireframeColor[0]);
					ImGui::NewLine(); ImGui::SameLine(0, 22);
					ImGui::SliderFloat("BVH nodes", &_renderingParams->_bvhNodesPercentage, 0.0f, 1.0f);

					this->leaveSpace(1);
				}

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Point cloud"))
			{
				this->leaveSpace(1);

				ImGui::SliderFloat("Point size", &_renderingParams->_lidarPointSize, 0.1f, 50.0f); 
				ImGui::ColorEdit3("Point cloud color", &_renderingParams->_lidarPointCloudColor[0]);

				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Wireframe"))
			{
				this->leaveSpace(1);

				ImGui::ColorEdit3("Wireframe color", &_renderingParams->_wireframeColor[0]);

				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}
	}

	ImGui::End();
}

void GUI::showSceneSettings()
{
	std::vector<Model3D::ModelComponent*>* modelComps = _renderer->getCurrentScene()->getModelComponents();

	ImGui::SetNextWindowSize(ImVec2(480, 440), ImGuiCond_FirstUseEver);

	if (ImGui::Begin("Scene Models", &_showSceneSettings, ImGuiWindowFlags_None))
	{
		// Apply changes button
		ImGui::PushID(0);
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1 / 7.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(1 / 7.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(1 / 7.0f, 0.8f, 0.8f));

		if (ImGui::Button("Apply changes"))
		{
			_renderer->getCurrentScene()->getRenderingGroup()->updateMeshSSBO();
		}

		ImGui::PopStyleColor(3);
		ImGui::PopID();

		this->leaveSpace(4);

		// Left
		static int modelCompSelected = 0;

		ImGui::BeginChild("Model Components", ImVec2(150, 0), true);

		for (int i = 0; i < modelComps->size(); ++i)
		{
			if (ImGui::Selectable(modelComps->at(i)->_name.c_str(), modelCompSelected == i))
				modelCompSelected = i;
		}

		ImGui::EndChild();

		ImGui::SameLine();

		// Right
		ImGui::BeginGroup();
		ImGui::BeginChild("Model Component View", ImVec2(0, -ImGui::GetFrameHeightWithSpacing()));		// Leave room for 1 line below us

		ImGui::Text(modelComps->at(modelCompSelected)->_name.c_str());
		ImGui::Separator();

		if (ImGui::BeginTabBar("Model Data", ImGuiTabBarFlags_None))
		{
			const vec2 nFloatBoundaries = vec2(.0f, 1.0f);

			if (ImGui::BeginTabItem("Settings"))
			{
				ImGui::SliderFloat("Opacity", &modelComps->at(modelCompSelected)->_opacity, nFloatBoundaries.x, nFloatBoundaries.y);
				ImGui::SliderFloat("Reflectance", &modelComps->at(modelCompSelected)->_reflectance, nFloatBoundaries.x, nFloatBoundaries.y);
				ImGui::SliderFloat("Shininess", &modelComps->at(modelCompSelected)->_shininess, nFloatBoundaries.x, nFloatBoundaries.y);
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::EndChild();
		ImGui::EndGroup();
	}

	ImGui::End();
}

GUI::~GUI()
{
	delete _customClasses;
	delete _lidarClasses;
}

/// [Public methods]

void GUI::initialize(GLFWwindow* window, const int openGLMinorVersion)
{
	const std::string openGLVersion = "#version 4" + std::to_string(openGLMinorVersion) + "0 core";

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(openGLVersion.c_str());
}

void GUI::render()
{
	bool show_demo_window = true;
	bool show_another_window = false;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	//if (show_demo_window)
	//	ImGui::ShowDemoWindow(&show_demo_window);

	this->createMenu();

	// Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}